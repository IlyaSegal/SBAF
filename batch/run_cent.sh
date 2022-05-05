#!/bin/bash

outfilenamemask=centrality
filenum=${SLURM_ARRAY_TASK_ID}
jobDir=${log_dir}/${filenum}

mkdir -p ${jobDir}
cd ${jobDir}
echo "current dir:" $PWD

elapsed=$SECONDS
glauberfile=${inputdir_glauber}/glauber_${filenum}.mcini.root
sbaffile=${outdir_sbaf}/${outfilenamemask}_${filenum}.sbaf
qafile=${outdir_qa}/${outfilenamemask}_qa_${filenum}

echo glauberfile: ${glauberfile}
echo sbaffile: ${sbaffile}
echo qafile: ${qafile}

#module load /cvmfs/vae.gsi.de/debian10/modules/linux-debian10-x86_64/gcc-10.2.0-gcc-8.3.0-envxzwl
seed=$(perl -e 'print int rand 99999999, "\n";')
echo seed: ${seed}

source $root_config
source $mcini_config
rsync -v $sbaf_config/macro/SampleGlauberEvent.C ${jobDir}
rsync -v $sbaf_config/macro/FillQA.C ${jobDir}
rsync -v $sbaf_config/macro/rootlogon.C ${jobDir}
sed -i -- "s~gRandom->SetSeed(0);~gRandom->SetSeed(${seed});~g" ${jobDir}/SampleGlauberEvent.C

files=10
for i in $(seq ${files}); do
if [ ! -e ${sbaffile} ];then
  root -b -l <<EOF
  .L SampleGlauberEvent.C
  SampleGlauberEvent("${glauberfile}", "${inputdir_histos}", "${sbaffile}_${i}.root", ${i}, ${events}, $AP, $ZP, $AT, $ZT, $pbeam, $ptarg, ${a}, ${b}, ${c}, ${ATotDependsOnB}, ${ATotDependsOnNSpec}, ${ProcedureMode}, ${FragDependsOnB},${FragDependsOnNSpec}, ${FragDependsOnATot}, ${EYDependsOnB}, ${EYDependsOnNSpec}, ${EYDependsOnATot}, ${EYDependsAFrag})
EOF
fi

if [ ! -e ${qafile} ];then
  root -b -l <<EOF
  .L FillQA.C
  FillQA("${sbaffile}_${i}.root", "${qafile}_${i}.root", $AP, $ZP, $AT, $ZT, $pbeam, $ptarg, "fixed-target")
EOF
fi
done

hadd -f ${sbaffile}.root ${sbaffile}_*
rm ${sbaffile}_*
hadd -f ${qafile}.root ${qafile}_*
rm ${qafile}_*

[ $remove_logs == 1 ] && rm -rf $log_dir/$filenum 

elapsed=$(expr $SECONDS - $elapsed)
echo "Done!"
echo Elapsed time: $(expr $elapsed / 60) minutes


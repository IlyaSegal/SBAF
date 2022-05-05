#!/bin/bash

#cbm
#export pbeam=2.3
#export pbeam=3.3
#export pbeam=5.36
#export pbeam=6
#export pbeam=8
#export pbeam=10
export pbeam=12
#export pbeam=30

#na49/61:
#export pbeam=14
#export pbeam=30
#export pbeam=40
#export pbeam=158

export ptarg=0

#system=pau
system=auau
#system=pbpb
#system=agag

export a=0.55                          # Stochastic term for full Procedure Mode / Gaussian mean value for light mode
export b=0.02                          # Constant term for full Procedure Mode / Gaussian sigma value for light mode
export c=0.16                          # Leakage term for full Procedure Mode / None for light mode
export ATotDependsOnB=true             # If ATot sampling depends on impact parameter
export ATotDependsOnNSpec=true         # If ATot sampling depends on number of spectators
export ProcedureMode=true              # Procedure Mode is false for light mode, true - for full mode
export FragDependsOnB=true             # If Fragments sampling depends on impact parameter
export FragDependsOnNSpec=true         # If Fragments sampling depends on number of spectators
export FragDependsOnATot=true          # If Fragments sampling depends on total mass number
export EYDependsOnB=false              # If EY sampling depends on impact parameter
export EYDependsOnNSpec=false          # If EY sampling depends on number of spectators
export EYDependsOnATot=true            # If EY sampling depends on total mass number
export EYDependsAFrag=true             # If EY sampling depends on fragment mass number

export events=2 # per file
jobRange=1
postfix=	
#partition=debug
partition=main
#partition=long

[ "$system" == "agag" ] && export AP=108 && export ZP=47 && export AT=108 && export ZT=47
[ "$system" == "auau" ] && export AP=197 && export ZP=79 && export AT=197 && export ZT=79
[ "$system" == "pbpb" ] && export AP=208 && export ZP=82 && export AT=208 && export ZT=82
[ "$system" == "pau" ] && export AP=1 && export ZP=1 && export AT=197 && export ZT=79

[ "$partition" == "debug" ] && time=0:20:00
[ "$partition" == "main" ] && time=8:00:00
[ "$partition" == "long" ] && time=1-00:00:00

export remove_logs=0 #"yes"

export root_config=/lustre/cbm/users/isegal/soft/root_v6-22-08_debian/install/bin/thisroot.sh
export mcini_config=/lustre/cbm/users/isegal/soft/mcini_debian/macro/config.sh
export glauber_config=/lustre/cbm/users/isegal/soft/glauber
export sbaf_config=/lustre/cbm/users/isegal/soft/SBAF

export inputdir_glauber="/lustre/cbm/users/isegal/mc/generators/glauber/auau/pbeam12agev/mbias/mcini/"
export inputdir_histos="/lustre/cbm/users/isegal/mc/centrality/dcmqgsm_smm/auau/pbeam12agev/mbias/PSDCentrality_Input_QA.root"

export outdir="/lustre/cbm/users/${USER}/mc/centrality/glauber/${system}/pbeam${pbeam}agev${postfix}/procedureMode_${ProcedureMode}/ATot_B${ATotDependsOnB}_NSpec${ATotDependsOnNSpec}/Frag_B${FragDependsOnB}_NSpec${FragDependsOnNSpec}_ATot${FragDependsOnATot}/EY_B${EYDependsOnB}_NSpec${EYDependsOnNSpec}_ATot${EYDependsOnATot}_AFrag${EYDependsAFrag}/"
export outdir_sbaf="$outdir/sbaf/"
export outdir_qa="$outdir/qa/"
export source_dir="$outdir/src/"
export log_dir="$outdir/log/"


mkdir -p "$outdir"
mkdir -p $source_dir
mkdir -p $outdir_sbaf
mkdir -p $outdir_qa
mkdir -p $log_dir

script_path=$(dirname ${0})
run_cent=${script_path}/run_cent.sh
rsync -vp $0 $source_dir 
rsync -vp ${run_cent} $source_dir
run_cent=${source_dir}/$(basename ${run_cent})

currentDir=`pwd`
echo "current dir:" $currentDir
echo "run_cent:" ${run_cent}

sbatch -J psd_cent_$pbeam -p $partition -t $time -a $jobRange -o ${log_dir}/%a_%A.log -D $outdir -- ${run_cent}

echo "========================================================"
echo "Output will be written to:"
echo ""
echo "source code: $source_dir"
echo "Temporary dir (do not forget to clean up after the jobs are finished) $log_dir"
echo "root files: $outdir_root"
echo ""
echo "dat files: $outdir_dat"
echo "glauber files: $outdir_glauber"
echo "glauber mcini files: $outdir_glauber_mcini"
echo "========================================================"



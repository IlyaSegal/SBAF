cmake_minimum_required(VERSION 3.1)
project(SBAF)

set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED)

list(APPEND CMAKE_PREFIX_PATH $ENV{MCINI})

if (NOT ROOT_FOUND)
    message(WARNING "ROOT was not found with CMAKE_PREFIX_PATH...")
    list(APPEND CMAKE_MODULE_PATH $ENV{ROOTSYS}/etc/cmake)
    find_package(ROOT REQUIRED)
endif ()

if (ROOT_USE_FILE)
    message("-- ROOT_USE_FILE ${ROOT_USE_FILE}")
    include(${ROOT_USE_FILE})
endif ()

if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9.0)
    message(WARNING "GCC compiler is older than 4.9.0. Boost library must be used!")
    find_package(Boost REQUIRED COMPONENTS regex)
    include_directories(${Boost_INCLUDE_DIRS})
endif ()

include_directories(${CMAKE_SOURCE_DIR})
include_directories($ENV{MCINI}/include)

ROOT_GENERATE_DICTIONARY(
        G__SBAF src/Event.h src/Fragment.h src/QA.h
        LINKDEF src/SBAFLinkDef.h
)
add_library(SBAF SHARED G__SBAF.cxx src/Event.cpp src/Fragment.cpp src/QA.cpp)
target_link_libraries(SBAF PRIVATE ${ROOT_LIBRARIES})

add_executable(FillQA macro/FillQA.C src/Event.h src/QA.h)
target_link_libraries(FillQA SBAF ${ROOT_LIBRARIES})

add_executable(MakeInput macro/InputFromBotvina.C src/Event.h src/Fragment.h)
target_link_libraries(MakeInput SBAF ${ROOT_LIBRARIES} $ENV{MCINI}/build/libMcIniData.so)

add_executable(SampleGlauberEvent macro/SampleGlauberEvent.C src/Event.h src/Fragment.h)
target_link_libraries(SampleGlauberEvent SBAF ${ROOT_LIBRARIES} $ENV{MCINI}/build/libMcIniData.so)
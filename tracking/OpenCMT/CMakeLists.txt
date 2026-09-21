project (CMT)

cmake_minimum_required (VERSION 2.6)

option(BUILD_TRAX_CLIENT "Build the trax client." OFF)

find_package(OpenCV REQUIRED)

add_definitions ("-Wall")
add_library(cmtlib  common.cpp 
    CMT.cpp Consensus.cpp Fusion.cpp Matcher.cpp Tracker.cpp
    fastcluster/fastcluster.cpp)
#add_executable (cmt_track common.cpp gui.cpp main.cpp CMT.h getopt/getopt.h getopt/getopt.c)
#add_executable (cmt_track   main.cpp  CMT.h )

target_link_libraries(cmtlib ${OpenCV_LIBS})

if(BUILD_TRAX_CLIENT)
    set(TRAX_DIR "" CACHE FILEPATH "Path to trax")

    include_directories(${TRAX_DIR}/include)

    add_executable (trax_client cmt common.cpp gui.cpp trax.cpp
        CMT.cpp Consensus.cpp Fusion.cpp Matcher.cpp Tracker.cpp
        fastcluster/fastcluster.cpp)

    find_library(TRAX_LIBRARY NAMES trax HINTS "${TRAX_DIR}/lib")

    target_link_libraries(trax_client ${OpenCV_LIBS} ${TRAX_LIBRARY})

endif()


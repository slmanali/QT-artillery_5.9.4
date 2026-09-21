project(STRUCK)

cmake_minimum_required(VERSION 2.6)

find_package(OpenCV REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

INCLUDE_DIRECTORIES ( src/GraphUtils ../eigen.2.0.17 ${OpenCV_INCLUDE_DIRS})
add_library(strucklib
    src/Config.cpp
    src/Features.cpp
    src/HaarFeature.cpp
    src/HaarFeatures.cpp
    src/HistogramFeatures.cpp
    src/ImageRep.cpp
    src/LaRank.cpp
    src/MultiFeatures.cpp
    src/RawFeatures.cpp
    src/Sampler.cpp
    src/Tracker.cpp
    src/GraphUtils/GraphUtils.cpp
	config.txt
    )
if(WITH_Test)	
add_executable(struck_track   src/main.cpp  src/Tracker.h)
target_link_libraries(struck_track  strucklib ${OpenCV_LIBS})
endif()
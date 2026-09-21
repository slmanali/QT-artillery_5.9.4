# Install script for directory: F:/tracker code/eigen.2.0.17/Eigen

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Eigen")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Program Files (x86)/Eigen/include/eigen2/Eigen/Core;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/LU;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/Cholesky;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/QR;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/Geometry;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/Sparse;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/Array;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/SVD;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/LeastSquares;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/QtAlignedMalloc;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/StdVector;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/NewStdVector;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/Eigen;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/Dense")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "C:/Program Files (x86)/Eigen/include/eigen2/Eigen" TYPE FILE FILES
    "F:/tracker code/eigen.2.0.17/Eigen/Core"
    "F:/tracker code/eigen.2.0.17/Eigen/LU"
    "F:/tracker code/eigen.2.0.17/Eigen/Cholesky"
    "F:/tracker code/eigen.2.0.17/Eigen/QR"
    "F:/tracker code/eigen.2.0.17/Eigen/Geometry"
    "F:/tracker code/eigen.2.0.17/Eigen/Sparse"
    "F:/tracker code/eigen.2.0.17/Eigen/Array"
    "F:/tracker code/eigen.2.0.17/Eigen/SVD"
    "F:/tracker code/eigen.2.0.17/Eigen/LeastSquares"
    "F:/tracker code/eigen.2.0.17/Eigen/QtAlignedMalloc"
    "F:/tracker code/eigen.2.0.17/Eigen/StdVector"
    "F:/tracker code/eigen.2.0.17/Eigen/NewStdVector"
    "F:/tracker code/eigen.2.0.17/Eigen/Eigen"
    "F:/tracker code/eigen.2.0.17/Eigen/Dense"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("F:/tracker code/eigen.2.0.17/build/Eigen/src/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)


# Install script for directory: F:/tracker code/eigen.2.0.17/Eigen/src

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

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("F:/tracker code/eigen.2.0.17/build/Eigen/src/Core/cmake_install.cmake")
  INCLUDE("F:/tracker code/eigen.2.0.17/build/Eigen/src/LU/cmake_install.cmake")
  INCLUDE("F:/tracker code/eigen.2.0.17/build/Eigen/src/QR/cmake_install.cmake")
  INCLUDE("F:/tracker code/eigen.2.0.17/build/Eigen/src/SVD/cmake_install.cmake")
  INCLUDE("F:/tracker code/eigen.2.0.17/build/Eigen/src/Cholesky/cmake_install.cmake")
  INCLUDE("F:/tracker code/eigen.2.0.17/build/Eigen/src/Array/cmake_install.cmake")
  INCLUDE("F:/tracker code/eigen.2.0.17/build/Eigen/src/Geometry/cmake_install.cmake")
  INCLUDE("F:/tracker code/eigen.2.0.17/build/Eigen/src/LeastSquares/cmake_install.cmake")
  INCLUDE("F:/tracker code/eigen.2.0.17/build/Eigen/src/Sparse/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)


# Install script for directory: F:/tracker code/eigen.2.0.17/Eigen/src/Core

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
   "C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Assign.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Block.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/CacheFriendlyProduct.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Coeffs.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/CommaInitializer.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Cwise.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/CwiseBinaryOp.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/CwiseNullaryOp.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/CwiseUnaryOp.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/DiagonalCoeffs.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/DiagonalMatrix.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/DiagonalProduct.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Dot.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Flagged.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Functors.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Fuzzy.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/GenericPacketMath.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/IO.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Map.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/MapBase.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/MathFunctions.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Matrix.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/MatrixBase.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/MatrixStorage.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Minor.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/NestByValue.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/NumTraits.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Part.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Product.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Redux.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/SolveTriangular.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Sum.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Swap.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Transpose.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core/Visitor.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Core" TYPE FILE FILES
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Assign.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Block.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/CacheFriendlyProduct.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Coeffs.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/CommaInitializer.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Cwise.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/CwiseBinaryOp.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/CwiseNullaryOp.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/CwiseUnaryOp.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/DiagonalCoeffs.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/DiagonalMatrix.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/DiagonalProduct.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Dot.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Flagged.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Functors.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Fuzzy.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/GenericPacketMath.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/IO.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Map.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/MapBase.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/MathFunctions.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Matrix.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/MatrixBase.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/MatrixStorage.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Minor.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/NestByValue.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/NumTraits.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Part.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Product.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Redux.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/SolveTriangular.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Sum.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Swap.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Transpose.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Core/Visitor.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("F:/tracker code/eigen.2.0.17/build/Eigen/src/Core/util/cmake_install.cmake")
  INCLUDE("F:/tracker code/eigen.2.0.17/build/Eigen/src/Core/arch/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)


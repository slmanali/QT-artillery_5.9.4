# Install script for directory: F:/tracker code/eigen.2.0.17/Eigen/src/Sparse

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Devel")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/AmbiVector.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/CholmodSupport.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/CompressedStorage.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/CoreIterators.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/DynamicSparseMatrix.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/MappedSparseMatrix.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/RandomSetter.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseAssign.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseBlock.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseCwise.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseCwiseBinaryOp.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseCwiseUnaryOp.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseDiagonalProduct.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseDot.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseFlagged.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseFuzzy.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseLDLT.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseLLT.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseLU.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseMatrix.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseMatrixBase.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseProduct.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseRedux.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseTranspose.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseUtil.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SparseVector.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/SuperLUSupport.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/TaucsSupport.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/TriangularSolver.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse/UmfPackSupport.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Sparse" TYPE FILE FILES
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/AmbiVector.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/CholmodSupport.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/CompressedStorage.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/CoreIterators.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/DynamicSparseMatrix.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/MappedSparseMatrix.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/RandomSetter.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseAssign.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseBlock.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseCwise.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseCwiseBinaryOp.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseCwiseUnaryOp.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseDiagonalProduct.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseDot.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseFlagged.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseFuzzy.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseLDLT.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseLLT.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseLU.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseMatrix.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseMatrixBase.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseProduct.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseRedux.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseTranspose.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseUtil.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SparseVector.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/SuperLUSupport.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/TaucsSupport.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/TriangularSolver.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Sparse/UmfPackSupport.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Devel")


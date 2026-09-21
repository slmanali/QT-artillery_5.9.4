# Install script for directory: F:/tracker code/eigen.2.0.17/Eigen/src/Geometry

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
   "C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Geometry/AlignedBox.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Geometry/AngleAxis.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Geometry/EulerAngles.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Geometry/Hyperplane.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Geometry/OrthoMethods.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Geometry/ParametrizedLine.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Geometry/Quaternion.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Geometry/Rotation2D.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Geometry/RotationBase.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Geometry/Scaling.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Geometry/Transform.h;C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Geometry/Translation.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "C:/Program Files (x86)/Eigen/include/eigen2/Eigen/src/Geometry" TYPE FILE FILES
    "F:/tracker code/eigen.2.0.17/Eigen/src/Geometry/AlignedBox.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Geometry/AngleAxis.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Geometry/EulerAngles.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Geometry/Hyperplane.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Geometry/OrthoMethods.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Geometry/ParametrizedLine.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Geometry/Quaternion.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Geometry/Rotation2D.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Geometry/RotationBase.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Geometry/Scaling.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Geometry/Transform.h"
    "F:/tracker code/eigen.2.0.17/Eigen/src/Geometry/Translation.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")


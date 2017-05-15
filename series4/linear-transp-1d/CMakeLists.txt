# Mandatory information that CMAKE needs
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)
# Project name
PROJECT (CMAEIIS3FD1D)

INCLUDE("cmake/CommonHeader.cmake")
INCLUDE("cmake/Compiler.cmake")


# So that Visual Studio will define M_PI
ADD_DEFINITIONS(-D_USE_MATH_DEFINES)
INCLUDE("cmake/GetEigen.cmake")


INCLUDE_DIRECTORIES(".")


SET(SRC_LT "linear_transport.cpp") # Source
ADD_EXECUTABLE(linear_transport ${SRC_LT}) 
ADD_DEPENDENCIES(linear_transport Eigen)

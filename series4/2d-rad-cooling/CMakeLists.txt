# Mandatory information that CMAKE needs
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

# Project name
PROJECT (2d-rad-cooling)

INCLUDE("cmake/CommonHeader.cmake")
INCLUDE("cmake/Compiler.cmake")
# So that Visual Studio will define M_PI
ADD_DEFINITIONS(-D_USE_MATH_DEFINES)
FIND_PACKAGE(Threads REQUIRED)
INCLUDE_DIRECTORIES(".")
INCLUDE_DIRECTORIES("..")
INCLUDE("cmake/GetEigen.cmake")
INCLUDE("cmake/GetIGL.cmake")

ADD_DEFINITIONS(-DNPDE_DATA_PATH="${CMAKE_CURRENT_SOURCE_DIR}/data/")

FILE(GLOB SRC *.cpp *.hpp)
ADD_EXECUTABLE(2d_rad_cooling ${SRC})
TARGET_LINK_LIBRARIES(2d_rad_cooling ${THREADS_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

ADD_DEPENDENCIES(2d_rad_cooling IGL Eigen )



cmake_minimum_required (VERSION 3.2.2)

project ("series1")

include ("../common/cmake/Common.cmake")

add_subdirectory (1d-FD)
add_subdirectory (2d-FD-porous)


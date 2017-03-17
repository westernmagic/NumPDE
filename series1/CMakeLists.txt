cmake_minimum_required (VERSION 3.7)

project ("NumPDE Series 1")

include ("../common/cmake/Common.cmake")

add_subdirectory (1d-FD)
add_subdirectory (2d-FD-porous)


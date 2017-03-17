cmake_minimum_required (VERSION 3.7)
project ("NumPDE Series 2")

enable_testing()
include ("../common/cmake/Common.cmake")

add_subdirectory (1d-linFEM)
add_subdirectory (2d-linFEM)


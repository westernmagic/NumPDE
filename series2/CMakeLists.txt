cmake_minimum_required (VERSION 3.2.2)
project ("series2")

enable_testing()
include ("../common/cmake/Common.cmake")

add_subdirectory (1d-linFEM)
add_subdirectory (2d-linFEM)


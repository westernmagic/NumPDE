cmake_minimum_required (VERSION 3.2.2)
project ("series4")

enable_testing()
include ("../common/cmake/Common.cmake")

add_subdirectory (2d-rad-cooling)
add_subdirectory (linear-transp-1d)


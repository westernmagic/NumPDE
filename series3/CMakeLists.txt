cmake_minimum_required (VERSION 3.2.2)
project ("series3")

enable_testing()
include ("../common/cmake/Common.cmake")

add_subdirectory (2d-poissonqFEM)
add_subdirectory (heateq_polar)


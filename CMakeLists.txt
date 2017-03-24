cmake_minimum_required (VERSION 3.7)
project ("NumPDE")

include ("common/cmake/Common.cmake")

enable_testing()

add_subdirectory (series0)
add_subdirectory (series1_warmup)
add_subdirectory (series1)
add_subdirectory (series2_warmup)
add_subdirectory (series2)


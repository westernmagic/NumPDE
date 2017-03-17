cmake_minimum_required (VERSION 3.7)

project ("series1")

include ("../common/cmake/Common.cmake")

add_subdirectory (1d-FD)
add_subdirectory (2d-FD-porous)

add_custom_target (submission COMMAND
	${CMAKE_COMMAND} -E tar "cfv" "series1.zip" --format=zip
	${CMAKE_CURRENT_SOURCE_DIR}
	${PROJECT_ROOT_DIR}/common
)


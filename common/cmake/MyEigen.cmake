set (EIGEN3_ROOT ${CMAKE_BINARY_DIR}/external/eigen)
file (MAKE_DIRECTORY ${EIGEN3_ROOT})

find_package (Eigen3 3.3 QUIET NO_MODULE)
if (NOT ${Eigen3_FOUND})
	execute_process (COMMAND
		${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}"
		${PROJECT_ROOT_DIR}/external/eigen
		WORKING_DIRECTORY ${EIGEN3_ROOT}
	)

	find_package (Eigen3 3.3 REQUIRED NO_MODULE)
endif (NOT ${Eigen3_FOUND})

get_property (MY_EIGEN TARGET Eigen3::Eigen PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
message ("Found Eigen3: ${MY_EIGEN}")


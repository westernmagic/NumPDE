set (GTEST_ROOT ${PROJECT_ROOT_DIR}/external/googletest/googletest)

if (NOT EXISTS ${GTEST_ROOT})
	message (STATUS "googletest not found… Downloading…")

	file (DOWNLOAD https://github.com/google/googletest/archive/master.zip ${PROJECT_ROOT_DIR}/external/googletest-master.zip)
	execute_process (COMMAND ${CMAKE_COMMAND} -E tar "x" ${PROJECT_ROOT_DIR}/external/googletest-master.zip "--format=zip")
	file (RENAME ${CMAKE_BINARY_DIR}/googletest-master ${PROJECT_ROOT_DIR}/external/googletest)
endif (NOT EXISTS ${GTEST_ROOT})

add_subdirectory (${GTEST_ROOT} googletest)
include (FindGTest)


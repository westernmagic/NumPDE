set (GTEST_ROOT ${PROJECT_ROOT_DIR}/external/googletest/googletest)

if (NOT EXISTS ${GTEST_ROOT})
	message (STATUS "googletest not found… Downloading…")

	file (DOWNLOAD https://github.com/google/googletest/archive/master.zip ${PROJECT_ROOT_DIR}/external/googletest-master.zip)
	execute_process (COMMAND ${CMAKE_COMMAND} -E tar "x" ${PROJECT_ROOT_DIR}/external/googletest-master.zip "--format=zip")
	file (RENAME ${CMAKE_BINARY_DIR}/googletest-master ${PROJECT_ROOT_DIR}/external/googletest)
endif (NOT EXISTS ${GTEST_ROOT})

add_subdirectory (${GTEST_ROOT} googletest)
set_property (TARGET gtest      PROPERTY EXCLUDE_FROM_ALL TRUE)
set_property (TARGET gtest_main PROPERTY EXCLUDE_FROM_ALL TRUE)

target_compile_options (gtest      PRIVATE -w)
target_compile_options (gtest_main PRIVATE -w)

include (FindGTest)


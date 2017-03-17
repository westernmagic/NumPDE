set (GTEST_ROOT ${PROJECT_ROOT_DIR}/external/googletest/googletest)
add_subdirectory (${GTEST_ROOT} googletest)
include (FindGTest)


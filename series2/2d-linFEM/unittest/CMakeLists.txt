file (GLOB SRC *.cpp)
include_directories (..)

add_executable (2d-linFEM-unittest ${SRC})
target_link_libraries(2d-linFEM-unittest Threads::Threads Eigen3::Eigen IGL::IGL gtest)

gtest_add_tests (2d-linFEM-unittest "" AUTO)
add_test (2d-linFEM-test 2d-linFEM-unittest)


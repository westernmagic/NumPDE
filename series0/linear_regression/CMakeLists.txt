file (GLOB SRC *.cpp *.hpp)
add_executable (linear_regression ${SRC})
target_link_libraries (linear_regression Eigen3::Eigen)


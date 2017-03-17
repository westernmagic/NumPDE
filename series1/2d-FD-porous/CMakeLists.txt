find_package (Eigen3 3.3 REQUIRED NO_MODULE)
add_executable (2d-FD-porous finite_difference.cpp)
target_link_libraries (2d-FD-porous Eigen3::Eigen)


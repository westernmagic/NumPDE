find_package (Eigen3 3.3 REQUIRED NO_MODULE)
add_executable (1d-FD finite_difference.cpp)
target_link_libraries (1d-FD Eigen3::Eigen)


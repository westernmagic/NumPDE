file (GLOB SRC *.cpp *.hpp)
add_executable (test_convergence ${SRC})
target_link_libraries (test_convergence midpoint)


file (GLOB SRC *.cpp *.hpp)
add_executable (test_single ${SRC})
target_link_libraries (test_single midpoint)


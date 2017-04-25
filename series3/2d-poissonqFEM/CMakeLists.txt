add_definitions (-DNPDE_DATA_PATH="${CMAKE_CURRENT_SOURCE_DIR}/data/")

FILE (GLOB SRC *.cpp *.hpp)

add_executable (fem2d ${SRC})
target_link_libraries (fem2d Threads::Threads Eigen3::Eigen IGL::IGL)


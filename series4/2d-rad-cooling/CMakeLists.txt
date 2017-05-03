add_definitions (-DNPDE_DATA_PATH="${CMAKE_CURRENT_SOURCE_DIR}/data/")

FILE (GLOB SRC *.cpp *.hpp)

add_executable (2d_rad_cooling ${SRC})
target_link_libraries (2d_rad_cooling Threads::Threads Eigen3::Eigen IGL::IGL)


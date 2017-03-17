add_subdirectory (unittest)

add_definitions (-DNPDE_DATA_PATH="${CMAKE_CURRENT_SOURCE_DIR}/data/")

FILE (GLOB SRC *.cpp *.hpp)

add_executable (2d-linFEM ${SRC})
target_link_libraries (2d-linFEM Threads::Threads Eigen3::Eigen IGL::IGL)


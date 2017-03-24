add_definitions (-DNPDE_DATA_PATH="${CMAKE_CURRENT_LIST_DIR}/")

FILE (GLOB SRC *.cpp *.hpp)

add_executable (2d-poissonlFEM ${SRC})
target_link_libraries (2d-poissonlFEM Threads::Threads Eigen3::Eigen IGL::IGL)


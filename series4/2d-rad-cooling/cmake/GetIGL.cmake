ExternalProject_Add(
    IGL
    URL https://github.com/libigl/libigl/archive/master.zip
    SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/IGL
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND "")
	include_directories(${CMAKE_CURRENT_BINARY_DIR}/IGL/include)	
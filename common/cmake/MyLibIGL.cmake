# adapted from
# https://github.com/libigl/libigl-example-project/blob/master/CMakeLists.txt
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                       ${PROJECT_ROOT_DIR}/external/libigl-example-project/cmake
)
set (ENV{LIBIGL} ${PROJECT_ROOT_DIR}/external/libigl)

find_package(LIBIGL MODULE REQUIRED)

if (LIBIGL_FOUND AND NOT TARGET IGL::IGL)
	# libigl options: choose between header only and compiled static library
	# Header-only is preferred for small projects. For larger projects the static build
	# considerably reduces the compilation times
	option (LIBIGL_USE_STATIC_LIBRARY "Use LibIGL as static library" OFF)

	# add a customizable menu bar
	option (LIBIGL_WITH_NANOGUI     "Use Nanogui menu"   OFF)

	# libigl options: choose your dependencies (by default everything is OFF except opengl) 
	option (LIBIGL_WITH_VIEWER      "Use OpenGL viewer"  OFF)
	option (LIBIGL_WITH_OPENGL      "Use OpenGL"         OFF)
	option (LIBIGL_WITH_OPENGL_GLFW "Use GLFW"           OFF)
	option (LIBIGL_WITH_BBW         "Use BBW"            OFF)
	option (LIBIGL_WITH_EMBREE      "Use Embree"         OFF)
	option (LIBIGL_WITH_PNG         "Use PNG"            OFF)
	option (LIBIGL_WITH_TETGEN      "Use Tetgen"         OFF)
	option (LIBIGL_WITH_TRIANGLE    "Use Triangle"       OFF)
	option (LIBIGL_WITH_XML         "Use XML"            OFF)
	option (LIBIGL_WITH_LIM         "Use LIM"            OFF)
	option (LIBIGL_WITH_COMISO      "Use CoMiso"         OFF)
	option (LIBIGL_WITH_MATLAB      "Use Matlab"         OFF) # This option is not supported yet
	option (LIBIGL_WITH_MOSEK       "Use MOSEK"          OFF) # This option is not supported yet
	option (LIBIGL_WITH_CGAL        "Use CGAL"           OFF)
	if (LIBIGL_WITH_CGAL) # Do not remove or move this block, the cgal build system fails without it
		find_package (CGAL REQUIRED)
		set (CGAL_DONT_OVERRIDE_CMAKE_FLAGS TRUE CACHE BOOL "CGAL's CMAKE Setup is super annoying ")
		include (${CGAL_USE_FILE})
	endif ()

	add_subdirectory ("${LIBIGL_INCLUDE_DIR}/../shared/cmake" "libigl")
	
	add_library (IGL::IGL INTERFACE IMPORTED)
	
	set_property (TARGET IGL::IGL PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${LIBIGL_INCLUDE_DIRS})
	set_property (TARGET IGL::IGL PROPERTY INTERFACE_COMPILE_OPTIONS ${LIBIGL_DEFINITIONS})
	set_property (TARGET IGL::IGL PROPERTY INTERFACE_SOURCES ${LIBIGL_EXTRA_SOURCES})
	set_property (TARGET IGL::IGL PROPERTY INTERFACE_LINK_LIBRARIES ${LIBIGL_LIBRARIES} ${LIBIGL_EXTRA_LIBRARIES})

	if (TARGET glew)
		set_property (TARGET glew         PROPERTY EXCLUDE_FROM_ALL TRUE)
		target_compile_options (glew         PRIVATE -w)
	endif (TARGET glew)

	if (TARGET glfw)
		set_property (TARGET glfw         PROPERTY EXCLUDE_FROM_ALL TRUE)
		target_compile_options (glfw         PRIVATE -w)
	endif (TARGET glfw)

	if (TARGET glfw_objects)
		set_property (TARGET glfw_objects PROPERTY EXCLUDE_FROM_ALL TRUE)
		target_compile_options (glfw_objects PRIVATE -w)
	endif (TARGET glfw_objects)

endif (LIBIGL_FOUND AND NOT TARGET IGL::IGL)


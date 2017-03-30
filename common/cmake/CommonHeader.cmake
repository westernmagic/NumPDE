set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED TRUE)

# adapted from
# https://github.com/RLovelett/eigen/blob/master/CMakeLists.txt

# guard against in-source builds
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message (FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

# guard against bad build-type strings
if (NOT CMAKE_BUILD_TYPE)
	set (CMAKE_BUILD_TYPE "Release")
endif (NOT CMAKE_BUILD_TYPE)

string (TOLOWER "${CMAKE_BUILD_TYPE}" cmake_build_type_tolower)
if (    NOT cmake_build_type_tolower STREQUAL "debug"
    AND NOT cmake_build_type_tolower STREQUAL "release"
    AND NOT cmake_build_type_tolower STREQUAL "relwithdebinfo")
	message(FATAL_ERROR "Unknown build type \"${CMAKE_BUILD_TYPE}\". Allowed values are Debug, Release, RelWithDebInfo (case-insensitive).")
endif ()


set (PROJECT_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/../..)

include_directories (${PROJECT_ROOT_DIR}/common/include)

# Don't make any install rules
set (CMAKE_SKIP_INSTALL_RULES TRUE)

include (CheckCXXCompilerFlag)
if (MSVC)
	foreach (i IN ITEMS /W4 /W44640)
		message (STATUS "Checking compiler support for ${i}")
		check_cxx_compiler_flag (${i} SUPPORTS_i)

		if (SUPPORTS_i)
			message (STATUS "Checking compiler support for ${i} - Success")
			add_compile_options (${i})
		else ()
			message (STATUS "Checking compiler support for ${i} - Failed")
		endif ()
	endforeach ()
else ()
	foreach (i IN ITEMS -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Weffc++)
		message (STATUS "Checking compiler support for ${i}")
		check_cxx_compiler_flag (${i} SUPPORTS_i)

		if (SUPPORTS_i)
			message (STATUS "Checking compiler support for ${i} - Success")
			add_compile_options (${i})
		else ()
			message (STATUS "Checking compiler support for ${i} - Failed")
		endif ()
		unset (SUPPORTS_i)
	endforeach ()
endif ()

find_package (OpenMP)
if (OPENMP_FOUND)
	list (APPEND CMAKE_C_FLAGS       ${OpenMP_C_FLAGS})
	list (APPEND CMAKE_CXX_FLAGS     ${OpenMP_CXX_FLAGS})
	list (APPEND CMAKE_FORTRAN_FLAGS ${OpenMP_Fortran_FLAGS})
endif (OPENMP_FOUND)

if (MSVC)
	# So that Visual Studio will define M_PI
	add_definitions (-D_USE_MATH_DEFINES)
endif (MSVC)


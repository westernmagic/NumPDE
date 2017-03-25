list (FIND CMAKE_CXX_COMPILE_FEATURES cxx_std_14 CXX_STD_14)

set (CXX_STD_MAX 11)
if (${CXX_STD_14} GREATER_EQUAL -1)
	set (CXX_STD_MAX 14)
endif (${CXX_STD_14} GREATER_EQUAL -1)

set (CMAKE_CXX_STANDARD ${CXX_STD_MAX})
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

add_compile_options (-Wall -Wextra)

if (MVSC)
        # So that Visual Studio will define M_PI
        add_definitions (-D_USE_MATH_DEFINES)
endif (MVSC)


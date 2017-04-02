# for submission generation
set (CPACK_GENERATOR "")
set (CPACK_SOURCE_GENERATOR "ZIP")
set (CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
list (APPEND CPACK_SOURCE_IGNORE_FILES build/ data/ .*\.mesh)

set (CPACK_SOURCE_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME}-${PROJECT_AUTHOR_SHORTNAME})

# add out-of-source directories
set (CPACK_SOURCE_INSTALLED_DIRECTORIES
	${CMAKE_SOURCE_DIR};/${CMAKE_PROJECT_NAME}
	${PROJECT_ROOT_DIR}/common;/common
	${PROJECT_ROOT_DIR}/external/libigl-example-project/cmake;/common/cmake
)
include (CPack)


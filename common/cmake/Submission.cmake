# for submission generation
set (CPACK_GENERATOR "")
set (CPACK_SOURCE_IGNORE_FILES "${CPACK_SOURCE_IGNORE_FILES};build/")
set (CPACK_SOURCE_GENERATOR "ZIP")
include (CPack)


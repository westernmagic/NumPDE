list (APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

include (CommonHeader)
include (${PROJECT_ROOT_DIR}/Settings.cmake)

include (MyEigen)
include (MyLibIGL)
include (MyThreads)
include (MyGTest)

include (Submission)


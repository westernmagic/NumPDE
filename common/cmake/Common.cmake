if (NOT DEFINED GUARD_${CMAKE_CURRENT_LIST_FILE})
	set (GUARD_${CMAKE_CURRENT_LIST_FILE} TRUE)
	list (APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

	include (CommonHeader)
	include (Settings)

	include (MyEigen)
	include (MyLibIGL)
	include (MyThreads)
	include (MyGTest)

	include (Submission)
endif (NOT DEFINED GUARD_${CMAKE_CURRENT_LIST_FILE})


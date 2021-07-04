add_executable(tests 
    unittests.cpp
	catch.hpp
)

if (UNIX)
target_link_libraries(tests 
    PUBLIC 
		${Boost_LIBRARIES}
		${ZLIB_LIBRARIES}
)
else ()
target_link_libraries(tests 
    PUBLIC 
		${Boost_LIBRARIES}
)
endif ()	
target_include_directories(tests 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		${Boost_INCLUDE_DIRS}
)




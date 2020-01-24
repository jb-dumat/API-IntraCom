set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(TEST_CLIENT ${PROJECT_NAME}-client)

add_executable(${TEST_CLIENT}
	main.cpp
)

create_target_directory_groups(${TEST_CLIENT})

target_link_libraries(${TEST_CLIENT} PRIVATE shared)
target_link_libraries(${TEST_CLIENT} PRIVATE Boost::boost -pthread)

if(UNIX AND NOT APPLE)
	install(TARGETS ${TEST_CLIENT} RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
endif()
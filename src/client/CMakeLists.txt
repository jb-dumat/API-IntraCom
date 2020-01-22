set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PAROC_CLIENT ${PROJECT_NAME}-client)

add_executable(${PAROC_CLIENT}
	main.cpp
)

create_target_directory_groups(${PAROC_CLIENT})

target_link_libraries(${PAROC_CLIENT} PRIVATE common)
target_link_libraries(${PAROC_CLIENT} PRIVATE Boost::boost -pthread)

if(UNIX AND NOT APPLE)
	install(TARGETS ${PAROC_CLIENT} RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
endif()
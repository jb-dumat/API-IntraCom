set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(TEST_SERVER ${PROJECT_NAME}-server)

add_executable(${TEST_SERVER}
	main.cpp

	Core.hpp
	utils/ConfigLoader.hpp
)

create_target_directory_groups(${TEST_SERVER})

target_link_libraries(${TEST_SERVER} PRIVATE shared)
target_link_libraries(${TEST_SERVER} PRIVATE Boost::boost yaml::yaml -pthread)

if(UNIX AND NOT APPLE)
	install(TARGETS ${TEST_SERVER} RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
endif()
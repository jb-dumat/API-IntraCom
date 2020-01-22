set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PAROC_SERVER ${PROJECT_NAME}-server)

add_executable(${PAROC_SERVER}
	main.cpp

	Core.hpp
	utils/ConfigLoader.hpp
)

create_target_directory_groups(${PAROC_SERVER})

target_link_libraries(${PAROC_SERVER} PRIVATE common)
target_link_libraries(${PAROC_SERVER} PRIVATE Boost::boost yaml::yaml -pthread)

if(UNIX AND NOT APPLE)
	install(TARGETS ${PAROC_SERVER} RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
endif()
add_library(sneuracom STATIC
		Client.hpp

		ClientManager.hpp

		Interpreter.cpp
		Interpreter.hpp

		ISocket.hpp

		NetworkService.hpp

		Server.hpp

		ServerManager.hpp

		TcpAcceptor.cpp
		TcpAcceptor.hpp

		TCPAsyncServer.hpp

		TcpSocket.cpp
		TcpSocket.hpp

		)

add_library(dneuracom SHARED
		Client.hpp

		ClientManager.hpp

		Interpreter.cpp
		Interpreter.hpp

		ISocket.hpp

		NetworkService.hpp

		Server.hpp

		ServerManager.hpp

		TcpAcceptor.cpp
		TcpAcceptor.hpp

		TCPAsyncServer.hpp

		TcpSocket.cpp
		TcpSocket.hpp

		)

set_target_properties(sneuracom PROPERTIES PUBLIC_HEADER "Client.hpp;ClientManager.hpp;Interpreter.hpp;ISocket.hpp;NetworkService.hpp;Server.hpp;TcpAcceptor.hpp;TCPAsyncServer.hpp;TcpSocket.hpp;")

create_target_directory_groups(sneuracom)
create_target_directory_groups(dneuracom)

target_link_libraries(sneuracom PUBLIC Boost::boost)
target_link_libraries(dneuracom PUBLIC Boost::boost)

if (UNIX AND NOT APPLE)
	install(TARGETS sneuracom ARCHIVE DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
	install(TARGETS dneuracom LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
elseif(APPLE)
	install(TARGETS sneuracom ARCHIVE DESTINATION "${CMAKE_SOURCE_DIR}/release_v1.0.0/lib" PUBLIC_HEADER DESTINATION "${CMAKE_SOURCE_DIR}/release_v1.0.0/include")
	install(TARGETS dneuracom LIBRARY DESTINATION "${CMAKE_SOURCE_DIR}/release_v1.0.0/lib")
endif()
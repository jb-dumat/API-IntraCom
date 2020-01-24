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

create_target_directory_groups(sneuracom)
create_target_directory_groups(dneuracom)

target_link_libraries(sneuracom PUBLIC Boost::boost)
target_link_libraries(dneuracom PUBLIC Boost::boost)

if (UNIX AND NOT APPLE)
	install(TARGETS sneuracom LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
	install(TARGETS dneuracom LIBRARY DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
endif()
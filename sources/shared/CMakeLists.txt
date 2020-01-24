add_library(shared STATIC
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

create_target_directory_groups(shared)

target_link_libraries(shared PUBLIC Boost::boost)
add_library(common STATIC
	Client.hpp

	ClientManager.hpp

	Interpreter.cpp
	Interpreter.hpp

	ISocket.hpp

	NetworkService.hpp

	ParocSession.hpp

	ParocSessionManager.hpp

	TcpAcceptor.cpp
	TcpAcceptor.hpp

	TCPAsyncServer.hpp

	TcpSocket.cpp
	TcpSocket.hpp
	)

create_target_directory_groups(common)

target_link_libraries(common PUBLIC Boost::boost)
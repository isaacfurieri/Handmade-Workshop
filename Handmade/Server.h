/*

  All code has been written by Karsten Vermeulen and may be used freely by anyone. It is by no
  means perfect and there is certainly room for improvement in some parts. As a whole, the code
  has been created as part of an engine for the purposes of educating other fellow programmers,
  and anyone else wishing to learn C++ and OOP. Feel free to use, copy, break, update and do as
  you wish with this code - it is there for all!

  UPDATED : June 2016

  -----------------------------------------------------------------------------------------------

- cannot create dot notation form for host because IP.host value is 0!!

- separate client socket. the main socket created is used to listen in on incoming connections.
  after a connection is made a new socket is created and used to send/recive messages! 

- did not create a network manager class because there is not much to manage, therefore rather
  created networking as a component.


*/

#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <SDL_net.h>

class Server
{

public :

	Server();

public:

	bool Initialize();

	bool SendData(const std::string& data);
	bool ReceiveData();

	bool Listen();
	
	void ShutDown();

private :

	int m_port;
	std::string m_name;
	
	IPaddress m_IP;
	TCPsocket m_socket;
	TCPsocket m_clientSocket;
	
};

#endif
#include <iostream>
#include "Client.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Client::Client()
{

	m_serverPort = 0;
	m_serverName = "";

}
//------------------------------------------------------------------------------------------------------
//function that initializes the network sub-system 
//------------------------------------------------------------------------------------------------------
bool Client::Initialize()
{

	//if network subsystem initialization failed, display error message and return false
	if (SDLNet_Init() == -1)
	{
		std::cout << "Network sub-system did not initialize properly." << std::endl;
		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that connects the client to a server
//------------------------------------------------------------------------------------------------------
bool Client::Connect(const std::string& serverName, int serverPort)
{

	//create IP object for client using server's ID and port value
	//if IP setup failed, display error message and return false
	if (SDLNet_ResolveHost(&m_IP, serverName.c_str(), serverPort) == -1)
	{
		std::cout << "Client IP could not be resolved." << std::endl;
		return false;
	}

	//create and connect TCP server socket 
	//this creates a connection between server and client sockets 
	m_socket = SDLNet_TCP_Open(&m_IP);

	//if client socket could not be connected, display error message and return false
	if (!m_socket)
	{
		std::cout << "Client socket could not be opened." << std::endl;
		return false;
	}

	//add server data to client properties!!
	m_serverPort = serverPort;
	m_serverName = serverName;

	//debug output!!
	std::cout << "Client successfully connected to " << "\"" << m_serverName << "\"" <<std::endl;

	return true;

}
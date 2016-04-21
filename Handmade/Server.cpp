#include <iostream>
#include "Server.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
Server::Server()
{

	m_port = 1234;
	m_name = "";
	m_socket = 0;

}
//------------------------------------------------------------------------------------------------------
//function that initializes the network sub-system and creates the server
//------------------------------------------------------------------------------------------------------
bool Server::Initialize()
{

	//if network subsystem initialization failed, display error message and return false
	if(SDLNet_Init() == -1)
	{
		std::cout << "Network sub-system did not initialize properly." << std::endl;
		return false;
	}

	//create IP object for server using port value
	//if IP setup failed, display error message and return false
	if (SDLNet_ResolveHost(&m_IP, NULL, m_port) == -1)
	{
		std::cout << "Server IP could not be resolved." << std::endl;
		return false;
	}

	//get name of server from IP
	m_name = SDLNet_ResolveIP(&m_IP);

	//debug output!!
	std::cout << "Server " << "\"" <<  m_name << "\"" << " created successfully." << std::endl;

	//create and open TCP server socket 
	//this creates an interface for server to connect with clients
	m_socket = SDLNet_TCP_Open(&m_IP);

	//if server socket could not be opened, display error message and return false
	if (!m_socket)
	{
		std::cout << "Server socket could not be opened." << std::endl;
		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that waits for a client to connect
//------------------------------------------------------------------------------------------------------
bool Server::Listen()
{

	//temporary client socket variable
	TCPsocket tempClientSocket = 0;

	//keep looping until a client connects
	//when a client connects, their socket will be opened
	while (!tempClientSocket)
	{
		tempClientSocket = SDLNet_TCP_Accept(m_socket);
		std::cout << "Waiting for client..." << std::endl;
	}

	//debug output!!
	std::cout << "Client has connected!" << std::endl;

	//add client socket to map
	m_clientSocketMap["CLIENT_1"] = tempClientSocket;

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that closes down network sub-system and sockets
//------------------------------------------------------------------------------------------------------
void Server::ShutDown()
{

	//loop through all elements in map and close each socket
	for (auto it = m_clientSocketMap.begin(); it != m_clientSocketMap.end(); it++)
	{
		SDLNet_TCP_Close(it->second);
	}

	//close down SDL networking sub-system
	SDLNet_Quit();

}
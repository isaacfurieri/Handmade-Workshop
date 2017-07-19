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

	m_clientSocket = 0;

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

	//open up socket connection using IP value created above which
	//will create a connection between server and client sockets 
	m_socket = SDLNet_TCP_Open(&m_IP);

	//if server socket could not be opened, display error message and return false
	if (!m_socket)
	{
		std::cout << "Server socket could not be opened." << std::endl;
		return false;
	}

	//get name of server from IP
	m_name = SDLNet_ResolveIP(&m_IP);

	//debug output!!
	std::cout << "Server " << "\"" <<  m_name << "\"" << " created successfully." << std::endl;

	return true;

}

//------------------------------------------------------------------------------------------------------
//function that sends data in string form to client...
//------------------------------------------------------------------------------------------------------
bool Server::SendData(const std::string& data)
{

	//first check if there is a socket connection before sending 
	//any data and display error message if there is no connection
	if (!m_clientSocket)
	{
		std::cout << "No socket connection. Cannot send data to client." << std::endl;
		return false;
	}

	//otherwise send data message via socket connection to client
	//if returned value is less than data sent error message!
	else
	{
		if (SDLNet_TCP_Send(m_clientSocket, data.c_str(), data.size() + 1) < (int)(data.size() + 1))
		{
			std::cout << "Error sending data to client.";
			return false;
		}

		else
		{
			std::cout << "Data sent to client." << std::endl;
		}
	}

	return true;

}

bool Server::ReceiveData()
{

	//..
	char data[2000];

	//first check if there is a socket connection before listening 
	//for any data and display error message if there is no connection
	if (!m_clientSocket)
	{
		std::cout << "No socket connection. Cannot receive data from client." << std::endl;
		return false;
	}

	//otherwise listen for data message via socket connection from client
	//if returned value is less than data sent error message!
	else
	{
		if (SDLNet_TCP_Recv(m_clientSocket, data, 2000) <= 0)
		{
			std::cout << "Error receiving data from client." << std::endl;
			return false;
		}

		else
		{
			std::cout << "Data received from client." << std::endl;
			std::cout << data << std::endl;
		}

	}

	return true;

}

//------------------------------------------------------------------------------------------------------
//function that waits for a client to connect
//------------------------------------------------------------------------------------------------------
bool Server::Listen()
{

	//keep listening in on open socket for client until they connect
	//if connection made store value in new socket variable
	while (!m_clientSocket)
	{
		m_clientSocket = SDLNet_TCP_Accept(m_socket);
		std::cout << "Waiting for client..." << std::endl;
	}

	//debug output!!
	std::cout << "Client has connected." << std::endl;

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that closes down network sub-system and sockets
//------------------------------------------------------------------------------------------------------
void Server::ShutDown()
{

	//close down socket connection
	SDLNet_TCP_Close(m_socket);
	
	//close down SDL networking sub-system
	SDLNet_Quit();

}
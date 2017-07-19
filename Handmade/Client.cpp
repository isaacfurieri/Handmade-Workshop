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
//function that sends data in string form to server
//------------------------------------------------------------------------------------------------------
bool Client::SendData(const std::string& data)
{

	//first check if there is a socket connection before sending 
	//any data and display error message if there is no connection
	if (!m_socket)
	{
		std::cout << "No socket connection. Cannot send data to server." << std::endl;
		return false;
	}

	//otherwise send data message via socket connection to server
	//if returned value is less than data sent error message!
	else
	{
		if (SDLNet_TCP_Send(m_socket, data.c_str(), data.size() + 1) < (int)(data.size() + 1))
		{
			std::cout << "Error sending data to server." << std::endl;
			return false;
		}

		else
		{
			std::cout << "Data sent to server." << std::endl;
		}
	}

	return true;

}

bool Client::ReceiveData()
{

	//..
	char data[2000];

	//first check if there is a socket connection before listening 
	//for any data and display error message if there is no connection
	if (!m_socket)
	{
		std::cout << "No socket connection. Cannot receive data from server." << std::endl;
		return false;
	}

	//otherwise listen for data message via socket connection from server
	//if returned value is less than data sent error message!
	else
	{
		if (SDLNet_TCP_Recv(m_socket, data, 2000) <= 0)
		{
			std::cout << "Error receiving data from server." << std::endl;
			return false;
		}

		else
		{
			std::cout << "Data received from server." << std::endl;
			std::cout << data << std::endl;
		}

	}

	return true;

}

//------------------------------------------------------------------------------------------------------
//function that connects the client to a server
//------------------------------------------------------------------------------------------------------
bool Client::Connect(const std::string& serverName, int serverPort)
{

	//variables that will store IP address in 32-bit and dot notation form
	//these values are used only for debugging purposes below
	unsigned int IPAddressLong;
	unsigned char IPAddressDot[4];
	
	//add server data to client properties!!
	m_serverPort = serverPort;
	m_serverName = serverName;

	//create IP object for client using server's ID and port value
	//if IP setup failed, display error message and return false
	if (SDLNet_ResolveHost(&m_IP, serverName.c_str(), serverPort) == -1)
	{
		std::cout << "Client IP could not be resolved." << std::endl;
		return false;
	}

	//open up socket connection using IP value created above which
	//will create a connection between server and client sockets 
	m_socket = SDLNet_TCP_Open(&m_IP);

	//if client socket could not be connected, display error message and return false
	if (!m_socket)
	{
		std::cout << "Client could not connect to " << "\"" << m_serverName << "\"." << std::endl;
		return false;
	}

	//debug output!!
	std::cout << "Client successfully connected to " << "\"" << m_serverName << "\"." << std::endl;

	//temporarily store IP address as a long 32-bit numerical value
	IPAddressLong = m_IP.host;

	//convert IP address value into a dot notation form ie 127.0.0.3
	//bitwise AND / bit shifting is used to convert each 8-bit portion
	//the formula below assumes bits are stored from left to right
	for (int i = 0; i < 4; i++)
	{
		IPAddressDot[i] = (unsigned char)(IPAddressLong & 255);
		IPAddressLong >>= 8;
	}

	//display IP address in dot notation form
	std::cout << "IP address is : " << (unsigned int)IPAddressDot[0] << "." << 
									   (unsigned int)IPAddressDot[1] << "." <<
		                               (unsigned int)IPAddressDot[2] << "." << 
									   (unsigned int)IPAddressDot[3] << std::endl;

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that closes down network sub-system and sockets
//------------------------------------------------------------------------------------------------------
void Client::ShutDown()
{

	//close down socket connection
	SDLNet_TCP_Close(m_socket);

	//close down SDL networking sub-system
	SDLNet_Quit();

}

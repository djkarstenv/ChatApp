#include <iostream>
#include "TCPConnection.h"

TCPConnection::TCPConnection()
{
    m_ip = {0, 0};
	m_listenSocket = nullptr;
	m_clientSocket = nullptr;
}

bool TCPConnection::Initialize(const char* address, int port)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "Error initializing SDL" << std::endl;
		system("pause");
		return false;
	}

	if (SDLNet_Init() == -1)
	{
		std::cout << "Error initializing SDL networking component." << std::endl;
		system("pause");
		return false;
	}

	if (SDLNet_ResolveHost(&m_ip, address, port) == -1)
	{
		std::cout << "Error resolving host." << std::endl;
		system("pause");
		return false;
	}

    return true;
}

bool TCPConnection::OpenSocket()
{
	m_listenSocket = SDLNet_TCP_Open(&m_ip);

	if (!m_listenSocket)
	{
		std::cout << "Error opening up socket for connection." << std::endl;
		system("pause");
		return false;
	}

    return true;
}

bool TCPConnection::ListenSocket()
{
	while (!m_clientSocket)
	{
		m_clientSocket = SDLNet_TCP_Accept(m_listenSocket);
		std::cout << ".";
		SDL_Delay(500);
	}

	SDLNet_TCP_Close(m_listenSocket);
    return true;
}

void TCPConnection::SendMessage(const std::string& message)
{
	int messageLength = message.length() + 1;

	if (SDLNet_TCP_Send(m_clientSocket, message.c_str(), messageLength) < messageLength)
	{
		std::cout << "Error sending message to client." << std::endl;
	}

	else
	{
		std::cout << "Message sent to client." << std::endl;
	}
}

void TCPConnection::ReceiveMessage(std::string& message)
{
	char tempMessage[BUFFER_SIZE] = {'\0'};

	if (SDLNet_TCP_Recv(m_clientSocket, tempMessage, BUFFER_SIZE) <= 0)
	{
		std::cout << "Error receiving message from client." << std::endl;
	}

	else
	{
		message = tempMessage;
	}
}

void TCPConnection::CloseSocket()
{
	SDLNet_TCP_Close(m_clientSocket);
}

void TCPConnection::Shutdown()
{
	SDLNet_Quit();
	SDL_Quit();
}
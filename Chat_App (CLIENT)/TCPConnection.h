#pragma once

#include <string>
#include <SDL.h>
#include <SDL_net.h>

const int BUFFER_SIZE = 2000;

class TCPConnection
{
public:

	TCPConnection();

public:

	bool Initialize(const char* address, int port);
	bool OpenSocket();
	
	void SendMessage(const std::string& message);
	void ReceiveMessage(std::string& message);

	void CloseSocket();
	void Shutdown();

private:

	IPaddress m_ip;
	TCPsocket m_socket;

};
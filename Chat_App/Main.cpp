#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_net.h>

const int PORT = 1234;

//message to send to the client(s)
std::string message;

//struct to store host address (IP) and port number
IPaddress ip;

//socket to listen in on incoming connections
TCPsocket listenSocket = nullptr;

//socket to transfer data to client
TCPsocket clientSocket = nullptr;

int main(int argc, char* argv[])
{

	//=============================================================
	//initialization
	//=============================================================

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "Error initializing SDL" << std::endl;
		system("pause");
		return 0;
	}

	if (SDLNet_Init() == -1)
	{
		std::cout << "Error initializing SDL networking component." << std::endl;
		system("pause");
		return 0;
	}

	//=============================================================
	//server code
	//=============================================================

	if (SDLNet_ResolveHost(&ip, nullptr, PORT) == -1)
	{
		std::cout << "Error creating a server." << std::endl;
		system("pause");
		return 0;
	}

	listenSocket = SDLNet_TCP_Open(&ip);

	if (!listenSocket)
	{
		std::cout << "Error opening up socket for connection." << std::endl;
		system("pause");
		return 0;
	}

	std::cout << "Server waiting for clients to connect." << std::endl;

	while (!clientSocket)
	{
		clientSocket = SDLNet_TCP_Accept(listenSocket);
		std::cout << ".";
		SDL_Delay(500);
	}

	SDLNet_TCP_Close(listenSocket);
	std::cout << "Client connected." << std::endl;
	system("pause");

	system("cls");
	std::cout << "#=============================#" << std::endl;
	std::cout << "| Welcome to Chat Master 2000 |" << std::endl;
	std::cout << "#=============================#" << std::endl;

	//create a friendly message for the client
	message = "Hello and welcome to my chat!";

	//we need length of message in order to send data
	//we add an extra space for the terminating null '\0'
	int messageLength = message.length() + 1;

	//send message via open socket that we opened up above
	//if return value is less than length of message then error occurred
	if (SDLNet_TCP_Send(clientSocket, message.c_str(), messageLength) < messageLength)
	{
		std::cout << "Error sending message to client." << std::endl;
	}

	else
	{
		std::cout << "Message sent to client." << std::endl;
	}

	SDLNet_TCP_Close(clientSocket);

	//shutdown tasks
	SDLNet_Quit();
	SDL_Quit();

	system("pause");
	return 0;
}
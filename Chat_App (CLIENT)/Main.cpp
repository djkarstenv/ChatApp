#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_net.h>

const int PORT = 1234;
const int BUFFER_SIZE = 2000;

//struct to store host address (IP) and port number
IPaddress ip;

//socket to transfer data to server
TCPsocket socket = nullptr;

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
	//client code
	//=============================================================

	if (SDLNet_ResolveHost(&ip, "127.0.0.1", PORT) == -1)
	{
		std::cout << "Error creating a client." << std::endl;
		system("pause");
		return 0;
	}

	socket = SDLNet_TCP_Open(&ip);

	if (!socket)
	{
		std::cout << "Error opening up socket for connection." << std::endl;
		system("pause");
		return 0;
	}

	std::cout << "Connected to server." << std::endl;
	system("pause");

	system("cls");
	std::cout << "#=============================#" << std::endl;
	std::cout << "| Welcome to Chat Master 2000 |" << std::endl;
	std::cout << "#=============================#" << std::endl;

	//place to store received message
	char message[BUFFER_SIZE];

	//receive message from server
	if (SDLNet_TCP_Recv(socket, message, BUFFER_SIZE) <= 0)
	{
		std::cout << "Error receiving message from server." << std::endl;
	}

	else
	{
		std::cout << message << std::endl;
	}

	SDLNet_TCP_Close(socket);

	//shutdown tasks
	SDLNet_Quit();
	SDL_Quit();

	system("pause");
	return 0;
}
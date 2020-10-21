#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_net.h>

int main(int argc, char* argv[])
{

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

	std::cout << "#=============================#" << std::endl;
	std::cout << "| Welcome to Chat Master 2000 |" << std::endl;
	std::cout << "#=============================#" << std::endl;

	IPaddress ip;

	if (SDLNet_ResolveHost(&ip, "www.londonmet.ac.uk", 80) == -1)
	{
		std::cout << "Error establishing connection with website." << std::endl;
		system("pause");
		return 0;
	}

	TCPsocket socket = SDLNet_TCP_Open(&ip);

	if (!socket)
	{
		std::cout << "Error opening up socket for connection." << std::endl;
		system("pause");
		return 0;
	}

	else
	{
		//special request to get HTML code from website
		std::string message = "GET /HTTPS/1.0\r\n\r\n";

		//we need length of message in order to send data
		//we add an extra space for the terminating null '\0'
		int messageLength = message.length() + 1;

		//send message via open socket that we opened up above
		//if return value is less than length of message then error occurred
		if (SDLNet_TCP_Send(socket, message.c_str(), messageLength) < messageLength)
		{
			std::cout << "Error sending request to website." << std::endl;
		}

		else
		{
			const int BUFFER_SIZE = 2000;

			char response[BUFFER_SIZE];

			if (SDLNet_TCP_Recv(socket, response, BUFFER_SIZE) <= 0)
			{
				std::cout << "Error receiving message from website." << std::endl;
			}

			else
			{
				std::cout << response << std::endl;
			}
		}

		SDLNet_TCP_Close(socket);

	}

	//shutdown tasks
	SDLNet_Quit();
	SDL_Quit();

	system("pause");
	return 0;
}
#include <iostream>
#include <string>
#include "TCPConnection.h"

const int PORT = 1234;
bool isAppRunning = true;

std::string message;
TCPConnection server;

int main(int argc, char* argv[])
{

	server.Initialize(nullptr, PORT);
	server.OpenSocket();

	std::cout << "Server waiting for clients to connect." << std::endl;

	server.ListenSocket();

	std::cout << "Client connected." << std::endl;
	system("pause");

	//==========================================================

	system("cls");
	std::cout << "#=============================#" << std::endl;
	std::cout << "| Welcome to Chat Master 2000 |" << std::endl;
	std::cout << "#=============================#" << std::endl;

	while (isAppRunning)
	{
		std::cout << ">";
		std::getline(std::cin, message);
		server.SendMessage(message);
		server.ReceiveMessage(message);
		std::cout << ">" + message << std::endl;
	}

	//==========================================================

	server.Shutdown();
	system("pause");
	return 0;
}
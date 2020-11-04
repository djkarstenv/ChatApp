#include <iostream>
#include <string>
#include "TCPConnection.h"

const int PORT = 1234;
bool isAppRunning = true;

std::string message;
TCPConnection client;

int main(int argc, char* argv[])
{

	std::string ip;
	std::cout << "Please enter the IP address: ";
	std::getline(std::cin, ip);
	client.Initialize(ip.c_str(), PORT);

	if (!client.OpenSocket())
	{
		return 0;
	}

	std::cout << "Client connected to server." << std::endl;
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
		client.SendMessage(message);
		client.ReceiveMessage(message);
		std::cout << ">" + message << std::endl;
	}

	//==========================================================

	client.Shutdown();
	system("pause");
	return 0;
}
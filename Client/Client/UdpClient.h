#pragma once
#include <Windows.h>
#include <winsock.h>
#include <iostream>
#include <string>

using namespace std;
class UdpClient
{
private:
	WSADATA WinSockData;
	SOCKET UDPSocketClient;
	struct sockaddr_in  UDPServer;
public:
	bool  InitWinsock();
	void  SetupServer(int af, char *ip, int port);
	bool  CreateSocket(int af);
	bool  SendData(char *buffer, int bufferSize);
	bool  RecvData(char* buffer, int bufferSize);
	bool  CloseSocket();
	bool  CleanWinSock();
};


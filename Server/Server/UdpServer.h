#pragma once
#include <Windows.h>
#include <winsock.h>
#include <iostream>
#include <string>
using namespace std;
class UdpServer
{
private:
	WSADATA WinSockData;
	SOCKET UDPSocketServer;
	struct sockaddr_in  UDPClient;
public:
	bool  InitWinsock();
	void  SetupClient(int af, char *ip, int port);
	bool  CreateSocket(int af);
	bool  Bind();
	bool  SendData(char* buffer, int bufferSize);
	bool  RecvData(char* buffer, int bufferSize);
	bool  CloseSocket();
	bool  CleanWinSock();
};


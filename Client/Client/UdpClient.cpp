#include "UdpClient.h"


bool UdpClient::InitWinsock()
{
	bool result = false;
	int isWsaStartup = 1;

	isWsaStartup = WSAStartup(MAKEWORD(2, 2), &WinSockData);
	if (isWsaStartup == 0)
	{
		result = true;
	}
	// else, do nothing.

	return result;
}

void UdpClient::SetupServer(int af, char *ip, int port)
{
	UDPServer.sin_family = af;
	UDPServer.sin_addr.S_un.S_addr = inet_addr(ip);
	UDPServer.sin_port = htons(port);
}

bool UdpClient::CreateSocket(int af)
{
	bool result = true;
	UDPSocketClient = socket(af, SOCK_DGRAM, IPPROTO_UDP);

	if (UDPSocketClient == INVALID_SOCKET)
	{
		result = false;
	}
	// else, do nothing.

	return result;
}

bool UdpClient::SendData(char* buffer, int bufferSize)
{
	bool result = true;
	int isDataSent = 1;
	isDataSent = sendto(UDPSocketClient, buffer, bufferSize, MSG_DONTROUTE, (SOCKADDR*)&UDPServer, sizeof(UDPServer) );
	if (isDataSent == SOCKET_ERROR)
	{
		result = false;
	}
	// else, do nothing.

	return result;
}

bool UdpClient::RecvData(char* buffer, int bufferSize)
{
	bool result = true;
	int isDataRec = 1;
	int udpClientLen = sizeof(UDPServer);

	isDataRec = recvfrom(UDPSocketClient, buffer, bufferSize, MSG_PARTIAL, (SOCKADDR*)&UDPServer, &udpClientLen);
	if (isDataRec == SOCKET_ERROR)
	{
		result = false;
	}
	// else, do nothing.

	return result;
}

bool UdpClient::CloseSocket()
{
	bool result = true;
	int isSocketClose;

	isSocketClose = closesocket(UDPSocketClient);
	if (isSocketClose == SOCKET_ERROR)
	{
		result = false;
	}
	// else, do nothing.

	return result;
}

bool UdpClient::CleanWinSock()
{
	bool result = true;
	int isWsaCleanup = 0;

	isWsaCleanup = WSACleanup();
	if (isWsaCleanup == SOCKET_ERROR)
	{
		result = false;
	}
	// else, do nothing.

	return result;
}

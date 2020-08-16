#include "UdpServer.h"

bool UdpServer::InitWinsock()
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

void UdpServer::SetupClient(int af, char *ip, int port)
{
	UDPClient.sin_family = af;
	UDPClient.sin_addr.S_un.S_addr = inet_addr(ip);
	UDPClient.sin_port = htons(port);
}

bool UdpServer::CreateSocket(int af)
{
	bool result = true;
	UDPSocketServer = socket(af, SOCK_DGRAM, IPPROTO_UDP);

	if (UDPSocketServer == INVALID_SOCKET)
	{
		result = false;
	}
	// else, do nothing.

	return result;
}

bool UdpServer::Bind()
{
	bool result = true;
	int isBind = 1;

	isBind = bind(UDPSocketServer, (SOCKADDR*)&UDPClient, sizeof(UDPClient) );
	if (isBind == SOCKET_ERROR)
	{
		result = false;
	}

	return result;
}

bool UdpServer::SendData(char* buffer, int bufferSize)
{
	bool result = true;
	int isDataSent = 1;
	isDataSent = sendto(UDPSocketServer, buffer, bufferSize, MSG_DONTROUTE, (SOCKADDR*)&UDPClient, sizeof(UDPClient));
	if (isDataSent == SOCKET_ERROR)
	{
		result = false;
	}
	// else, do nothing.

	return result;
}

bool UdpServer::RecvData(char* buffer, int bufferSize)
{
	bool result = true;
	int isDataRec = 1;
	int udpClientLen = sizeof(UDPClient);

	isDataRec = recvfrom(UDPSocketServer, buffer, bufferSize, MSG_PARTIAL, (SOCKADDR*)&UDPClient, &udpClientLen);
	if (isDataRec == SOCKET_ERROR)
	{
		result = false;
	}
	// else, do nothing.

	return result;
}

bool UdpServer::CloseSocket()
{
	bool result = true;
	int isSocketClose;

	isSocketClose = closesocket(UDPSocketServer);
	if (isSocketClose == SOCKET_ERROR)
	{
		result = false;
	}
	// else, do nothing.

	return result;
}

bool UdpServer::CleanWinSock()
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

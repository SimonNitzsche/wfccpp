#pragma once
#pragma comment(lib, "Ws2_32.lib")
#include "udp_client_server.h"


#define DBL 32000
#include "UDPPacket.h"

class UDPManager {
private:
	udp_client_server::udp_server m_server;
	//udp_client_server::udp_client m_client;

	char packetBuffer[DBL];
public:
	UDPManager(const std::string& addr, int port);

	int getPacket(char* outData, int dataBufferLen, sockaddr* outFrom, int* outFromLen);
	int getPacket(char* outData, int dataBufferLen, sockaddr* outFrom);
	int getPacket(sockaddr* outFrom);
	UDPPacket getPacket();
	void ReturnToSender(UDPPacket* outgoingPacket);
};
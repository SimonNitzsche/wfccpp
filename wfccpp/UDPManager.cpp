#pragma once
#include "UDPManager.h"

UDPManager::UDPManager(const std::string& addr, int port) : m_server(addr, port)/*, m_client(addr, port)*/ {

}

int UDPManager::getPacket(char * outData, int dataBufferLen, sockaddr * outFrom, int * outFromLen) {
	return ::recvfrom(m_server.get_socket(), outData, dataBufferLen, 0, outFrom, outFromLen);
}

int UDPManager::getPacket(char* outData, int dataBufferLen, sockaddr* outFrom) {
	int sas = sizeof(sockaddr);
	return getPacket(outData, dataBufferLen, outFrom, &sas);
}

int UDPManager::getPacket(sockaddr* outFrom) {
	return getPacket(this->packetBuffer, DBL, outFrom);
}

UDPPacket UDPManager::getPacket() {
	UDPPacket resp;

	resp.bytesAllocated = DBL;
	resp.data = nullptr;

	sockaddr_in sadin;
	resp.bytesWritten = getPacket(reinterpret_cast<sockaddr*>(&sadin));
	
	if (resp.bytesWritten != -1) {
		resp.origin = sadin;
		resp.data = reinterpret_cast<uint8_t*>(packetBuffer);
	}

	return resp;
}

std::string getIPStr(sockaddr_in * ipv4) {
	char ipAddress[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(ipv4->sin_addr), ipAddress, INET_ADDRSTRLEN);
	return std::string(ipAddress);
}

void UDPManager::ReturnToSender(UDPPacket* outgoingPacket) {
	udp_client_server::udp_client m_client(getIPStr(&outgoingPacket->origin), outgoingPacket->origin.sin_port);
	m_client.send(reinterpret_cast<const char*>(outgoingPacket->data), outgoingPacket->bytesWritten);
}
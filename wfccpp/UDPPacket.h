#pragma once
#include <memory>

#include "udp_client_server.h"

class UDPPacket {
public:
	uint8_t* data = nullptr;
	uint32_t bytesWritten = 0;
	uint32_t bytesAllocated = 0;
	uint32_t readOffset = 0;
	sockaddr_in origin;

	template<typename T>
	void Read(T & v) {
		v = Read<T>();
	}


	template<typename T>
	T Read() {
		T * v =  reinterpret_cast<T*>(data + readOffset);
		readOffset += sizeof(T);
		return *v;
	}

	template<typename T0, typename T1>
	void ReadRange(T0& t0, T1& t1) {
		size_t size = reinterpret_cast<uint8_t*>(&t1) - reinterpret_cast<uint8_t*>(&t0) + sizeof(T1);
		memcpy_s(reinterpret_cast<void* const>(&t0), size, reinterpret_cast<const void* const>(data), size);
		readOffset += size;
	}

	void ReadCString(unsigned char* & v) {
		v = reinterpret_cast<uint8_t*>(data) + readOffset;
	}

	template<typename T>
	void Write(T& v) {
		memcpy_s(reinterpret_cast<void* const>(data + bytesWritten), sizeof(T), reinterpret_cast<const void* const>(&v), sizeof(T));
		bytesWritten += sizeof(T);
	}

	void prepareForResponse() {
		bytesWritten = 0;
		readOffset = 0;
	}
};


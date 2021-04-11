#pragma once

#include <memory>
#include "le_types.h"
#include "UDPPacket.h"

namespace QSServicePackets {
	enum class EPacketType : uint8_t {
		AVAILABLE = 9
	};

	class I_PK_IncomingPacket {
	public:
		EPacketType packetType;

		void ReadBase(UDPPacket* packet) {
			packetType = packet->Read<EPacketType>();
		}
	};

	class I_PK_OutgoingPacket {
	public:
		uint8_t magicResponse[2] = { 0xfe, 0xfd };
		EPacketType packetType;

		void WriteBase(UDPPacket * packet){
			packet->Write(magicResponse[0]);
			packet->Write(magicResponse[1]);
			packet->Write(packetType);
		}
	};

	class PK_Available_Incoming : public I_PK_IncomingPacket {
	public:
		le_u32 status;
		unsigned char* gamename;

		void Read(UDPPacket * packet) {
			status = packet->Read<uint32_t>();
			packet->ReadCString(gamename);
		}
	};

	class PK_Available_Outgoing : public I_PK_OutgoingPacket {
	public:
		le_u32 status;

		void Write(UDPPacket* packet) {
			I_PK_OutgoingPacket::WriteBase(packet);
			packet->Write(status);
		}
	};
}
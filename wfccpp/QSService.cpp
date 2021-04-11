#include "QSService.h"
#include "UDPPacket.h"
#include <iostream>
#include "QSServicePackets.h"

void QSService::launch() {
	std::cout << "QSService launched." << std::endl;
}

void QSService::loop() {
	// listen for packet
	UDPPacket incomingPacket = qsService.getPacket();

	// Read head
	QSServicePackets::I_PK_IncomingPacket pkIncomingPacket;
	pkIncomingPacket.ReadBase(&incomingPacket);

	/*
	================================
		THE MIGHTY PACKET SWITCH    
	================================
	*/
	switch (pkIncomingPacket.packetType) {
	case QSServicePackets::EPacketType::AVAILABLE: {

		// Read packed
		QSServicePackets::PK_Available_Incoming pkAvailableIncoming;
		pkAvailableIncoming = *reinterpret_cast<QSServicePackets::PK_Available_Incoming*>(&pkIncomingPacket);
		pkAvailableIncoming.Read(&incomingPacket);

		// Respond
		UDPPacket outgoingPacket = incomingPacket;
		outgoingPacket.prepareForResponse();

		QSServicePackets::PK_Available_Outgoing pkAvailableOutgoing;
		pkAvailableOutgoing.packetType = pkAvailableIncoming.packetType;
		
		// 0 = Online, 1 = Shutdown permanentely, 2 = Maintenance
		pkAvailableOutgoing.status = 0;
		
		pkAvailableOutgoing.Write(&outgoingPacket);

		qsService.ReturnToSender(&outgoingPacket);

		break;
	}
	}
}

#pragma once
#include "IService.h"
#include "UDPManager.h"

class QSService : public IService {
public:
	UDPManager qsService = UDPManager("0.0.0.0", 27900);

	void launch();
	void loop();
};


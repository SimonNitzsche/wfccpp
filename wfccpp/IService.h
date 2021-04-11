#pragma once
#include <thread>
class IService {
private:
	std::thread sT;
public:
	bool m_running = false;

	void setup() {
		launch();
		m_running = true;

		sT = std::thread(T_SERVICE_THREAD, this);
		sT.detach();
	}
private:
	static void T_SERVICE_THREAD(IService * self) {
		while (self->m_running) {
			self->loop();
		}
	}
public:
	virtual void launch() = 0;
	virtual void loop() = 0;
};


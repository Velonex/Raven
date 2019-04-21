#include <NightFall.h>

class TestApp : public nfe::NightFallApplication {

};

TestApp app;

//class TestEvent : public nfe::Event {
//public:
//	TestEvent(int x) : nfe::Event(nfe::EventType::EVENT_TEST, "TestEvent") {
//		this->x = x;
//	}
//	int x = 0;
//};
//
//class Recieva : public nfe::EventListener {
//public:
//	virtual void onEvent(nfe::Event* e) override {
//		if (e->getType() == nfe::EventType::EVENT_TEST)
//			LOG_TRACE("{}", ((TestEvent*)e)->x);
//	}
//};

int main() {
	app.setInstance(&app);
	app.init((char*)"TestApp");

}
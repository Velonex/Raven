#include <NightFall.h>
#include <imgui.h>
#include <glad/glad.h>

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
class TestLayer : public nfe::Layer {
public:
	TestLayer() {

	}
	virtual void onImGuiRender() override {
		ImGui::Begin("TestWindow");
		ImGui::Text("Test");
		ImGui::End();
		//float verts[9] = {
		//	 0.0,  0.5,  0.0,
		//	-0.5, -0.5,  0.0,
		//	 0.5, -0.5,  0.0
		//};
		//unsigned int buffer;
		//glGenBuffers(1, &buffer);
		//glBindBuffer(GL_ARRAY_BUFFER, buffer);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(float)*9, verts, GL_STATIC_)
	}
};
int main() {
	app.setInstance(&app);
	app.init((char*)"TestApp");
	TestLayer* lyr = new TestLayer();
	app.getLayerStack()->pushOverlay(lyr);
	app.run();
	return app.quit();
}
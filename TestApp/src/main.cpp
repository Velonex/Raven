#include <NightFall.h>
#include <imgui.h>
#include <glad/glad.h>

class TestApp : public nfe::NightFallApplication {

};

TestApp app;

class TestLayer : public nfe::Layer {
public:
	TestLayer() {

	}
	virtual void onImGuiRender() override {
		ImGui::Begin("TestWindow");
		ImGui::Text("Test");
		ImGui::End();
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
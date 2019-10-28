#include <Raven.h>
#include <Sandbox.h>
#include <Sandbox2D.h>

class TestApp : public rvn::Application {
};

TestApp app;



int main() {
	app.setInstance(&app);
	app.init((char*)"TestApp");
	auto* lyr = new Sandbox2D();
	app.getLayerStack()->pushOverlay(lyr);
	app.run();
	return app.quit();
}
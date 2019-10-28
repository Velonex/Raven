#include <Raven.h>
#include <Sandbox.h>

class TestApp : public rvn::Application {
};

TestApp app;



int main() {
	app.setInstance(&app);
	app.init((char*)"TestApp");
	Sandbox* lyr = new Sandbox();
	app.getLayerStack()->pushOverlay(lyr);
	app.run();
	return app.quit();
}
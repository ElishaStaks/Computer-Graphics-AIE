#include "ComputerGraphicsApp.h"

int main() {

    auto* app = new ComputerGraphicsApp();

	if (app->startUp() == true) {
		while (app->update(0.01f))
			app->draw();
		    app->shutDown();
	}

	delete app;
	return 0;
}
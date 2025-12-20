#include "AxionForge.h"

namespace AxionForge {

	Application::Application() {
		INIT();
	}

	void Application::INIT() {
		if (SDL_Init(SDL_INIT_VIDEO))
			Console::Log("SDL initialized successfully.");
		else
			Console::Error("Failed to initialize SDL: " + std::string(SDL_GetError()));

		window = new Window("Axion Forge Application", 1000, 500);
		window->setBackgroundColor(ColorName::White);
		window->renderer.SetVSync(1);
	}

	void Application::RUN() {
		while (isRunning) {



		}
	}
	void Application::QUIT() {
		SDL_Quit();
		Console::Log("SDL quit successfully.");
	}

}

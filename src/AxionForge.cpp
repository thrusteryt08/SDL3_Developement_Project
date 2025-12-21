#include "AxionForge.h"

namespace AxionForge {

	Application::Application() {
		Console::Log("Starting Axion Forge Application...\n");
		INIT();
	}

	void Application::INIT() {
		Console::Log("Initializing Axion Forge Application...", 1);

		Console::Log("Initializing SDL...", 2);
		if (SDL_Init(SDL_INIT_VIDEO))
			Console::Log("SDL initialized successfully.", 2);
		else
			Console::Error("--Failed to initialize SDL", SDL_GetError(), 2);

		Console::Log("Creating main application window...", 2);
		window = new Window("Axion Forge Application", 1000, 500);
		window->setBackgroundColor(ColorName::White);
		window->renderer.SetVSync(1);
		window->Objects.Add(new ColorRect(Vector2(50), Vector2(200), ColorName::Red));
		Console::Log("Main application window created successfully.", 2);

		Console::Log("Application initialized successfully.\n", 1);
	}

	void Application::RUN() {
		Console::Log("Running Axion Forge Application...", 1);
		while (isRunning) {
			Event event;
			while (EventPump::Pull(event)) {
				if (event.GetType() == EventType::QUIT)
					return;

				switch (event.GetType())
				{

				default:
					break;
				}
			}

			window->Render();
		}
	}
	void Application::QUIT() {
		Console::Log("Application run loop has ended.\n", 1);

		Console::Log("Quitting Axion Forge Application...", 1);

		Console::Log("Destroying main application window...", 2);
		delete window;
		window = nullptr;
		Console::Log("Main application window destroyed successfully.", 2);
		Console::Log("Quitting SDL...", 2);
		SDL_Quit();
		Console::Log("SDL quit successfully.", 2);
		Console::Log("Axion Forge Application has exited.\n", 1);
		Console::Log("Thank you for using Axion Forge!");
	}

}

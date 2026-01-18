#include "SDL3/SDL.h"
#include <iostream>

#include "Window.h"
#include "Console.h"
#include "Label.h"
#include "Button.h"
#include "TextBox.h"


namespace AxionForge {

	class Application {
		Window* window = nullptr;

		void INIT_SDL() {
			Console::Log("Initializing SDL...");

			if (SDL_Init(SDL_INIT_VIDEO))
				Console::Log("SDL initialized successfully.");
			else
				Console::Error("Failed to initialize SDL");
		}

		void QUIT_SDL() {
			Console::Log("Quitting SDL...");

			SDL_Quit();

			Console::Log("SDL quit successfully.");
		}

		void CreateWindow() {
			Console::Log("Creating main application window...");

			window = new Window("Axion Forge Application", 1000, 500);
			window->setBackgroundColor(ColorName::White);
			window->setVSync(1);

			Console::Log("Main application window created successfully.");
		}

		void DestroyWindow() {
			Console::Log("Destroying main application window...");

			delete window;
			window = nullptr;

			Console::Log("Main application window destroyed successfully.");
		}

	public:
		Application() {
			Console::Log("Starting Axion Forge Application...");

			INIT();
			RUN();
			QUIT();

			Console::Log("Thank you for using Axion Forge!");
		}
		void INIT() {
			Console::Log("Initializing Axion Forge Application...");

			INIT_SDL();
			CreateWindow();

			AppLoad();


			Console::Log("Application initialized successfully.");
		}
		void RUN() {
			Console::Log("Running Axion Forge Application...");

			bool appState = true;

			while (appState) {

				Iterate(appState);

				SDL_Event event;
				while (SDL_PollEvent(&event)) {
					Event* e = SDLEventTranslator::Translate(event);

					if (!e)continue;
					if (window->HandleEvents(*e))
						return;

					AppEvent(*e);

					delete e;
				}

				window->Render();
			}
			Console::Log("Application run loop has ended.\n");
		}
		void QUIT() {
			Console::Log("Quitting Axion Forge Application...");
			//

			Exit();


			DestroyWindow();

			QUIT_SDL();

			//
			Console::Log("Axion Forge Application has exited.\n");

		}

		void AppLoad();

		void Iterate(bool& _appState);

		void AppEvent(Event& e);

		void Exit();

	};

}
#include "Core/Window.h"
#include <SDL3/SDL.h>

namespace AxionForge {

	Window::Window() = default;

	Window::Window(const char* title, int width, int height) {
		Create(title, width, height);
	}

	void Window::Create(const char* title, int width, int height) {
		if (window) {
			SDL_DestroyWindow(window);
			window = nullptr;
		}

		Width = width;
		Height = height;

		SDL_CreateWindowAndRenderer(
			title,
			width,
			height,
			0,
			&window,
			renderer.InstanceAddress()
		);
	}

	void Window::setBackgroundColor(Color color) {
		backgroundcolor = color;
	}

	void Window::Resize(Vector2 size) {
		Resize((int)size.x, (int)size.y);
	}

	void Window::Resize(int x, int y) {
		Width = x;
		Height = y;
		SDL_SetWindowSize(window, Width, Height);
	}

	void Window::setScale(float x) {
		Scale = x;
		renderer.setScale(Scale);
	}

	void Window::setDelay(int x) {
		Delay = x;
	}

	void Window::RenderObjects() {
		for (auto& object : Objects) {
			if (object) {
				if (object->isShown())
					renderer.RenderObject(object);
			}
		}
	}

	void Window::Render() {
		renderer.setDrawColor(backgroundcolor);
		renderer.Clear();
		RenderObjects();
		renderer.Present();
		renderer.Delay(Delay);
	}

	Window::~Window() {
		if (window) {
			SDL_DestroyWindow(window);
			window = nullptr;
		}
	}

}
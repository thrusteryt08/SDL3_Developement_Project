#pragma once
#include "Color.h"
#include "LinkedList.h"
#include "Object.h"
#include "Renderer.h"
#include "Control.h"
namespace AxionForge {

	class Window {
#pragma region private
	private:
		SDL_Window* window = nullptr;
		Color backgroundcolor = ColorName::White;

		Renderer renderer;
		bool change = false;

		int Width = 500;
		int Height = 500;
		float Scale = 1.0f;

		bool isDragSelectingEnabled = false;

		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(Window&&) = delete;

#pragma endregion

	public:
		LinkedList<Object*> Objects;

		Window() = default;
		Window(const char* title, int width, int height) {
			Create(title, width, height);
		}

		void Create(const char* title, int width, int height) {
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

		void setBackgroundColor(Color color) {
			backgroundcolor = color;
		}

		Vector2 getSize() const {
			return Vector2(Width, Height);
		}
		void Resize(Vector2 size) {
			Resize((int)size.x, (int)size.y);
		}
		void Resize(int x, int y) {
			Width = x;
			Height = y;
			SDL_SetWindowSize(window, Width, Height);
		}

		float getScale() const {
			return Scale;
		}
		void setScale(float x) {
			Scale = x;
			renderer.setScale(Scale);
		}

		void Delay(int x) {
			SDL_Delay(x);
		}
		void DelayNS(int x) {
			SDL_DelayNS(x);
		}

		void RenderObjects() {
			for (Object* object : Objects) {
				if (object && object->isShown())
					object->Render(&renderer);
			}
		}

		bool isChanged() const {
			return change;
		}

		void setVSync(int x) {
			renderer.SetVSync(x);
		}

		void BakeRender() {
			renderer.setDrawColor(backgroundcolor);
			renderer.Clear();
			RenderObjects();
		}

		void BakeNewObjects(Object* object) {
			renderer.RenderObject(object);
		}

		void Render() {
			BakeRender();
			renderer.Present();
		}

		void HandleEvents() {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				Event* e = SDLEventTranslator::Translate(event);

				if (!e)continue;

				for (Object* object : Objects) {
					if (Control* control = dynamic_cast<Control*>(object))
						control->OnEvent(*e);
				}

				EventDispatcher dispatcher(*e);


				delete e;
			}
		}




		~Window() {
			if (window) {
				SDL_DestroyWindow(window);
				window = nullptr;
			}
		}
	};

}
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
		bool isDragSelecting = false;
		Vector2 dragSelectStart;
		ColorRect dragSelectRect;

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
			//temporary for testing
			isDragSelectingEnabled = true;
			Objects.Add(&dragSelectRect);
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

		bool HandleEvents() {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				Event* e = SDLEventTranslator::Translate(event);

				if (!e)continue;

				EventDispatcher d(*e);

				d.Dispatch<QuitEvent>([this](QuitEvent& ev) {
					return true;
					});
				if(e->Handled)
					return true;

				if (isDragSelectingEnabled) {
					d.Dispatch<MouseButtonDownEvent>([this](MouseButtonDownEvent& ev) {
						if (ev.Button != 1) return false;
						isDragSelecting = true;
						dragSelectStart = ev.Position;
						return true;
						});

					d.Dispatch<MouseMoveEvent>([this](MouseMoveEvent& ev) {
						if (!isDragSelecting) return false;
						Vector2 currentPos = ev.Position;
						Vector2 rSize = currentPos - dragSelectStart;
						if (rSize < Vector2(0))
							dragSelectRect = ColorRect(currentPos, Vector2(-rSize.x, -rSize.y), Color(0, 0, 255, 100));
						else
							dragSelectRect = ColorRect(dragSelectStart, rSize, Color(0, 0, 255, 100));

						return true;
						});

					d.Dispatch<MouseButtonUpEvent>([this](MouseButtonUpEvent& ev) {
						if (!isDragSelecting) return false;
						isDragSelecting = false;
						dragSelectRect = ColorRect(Vector2(0, 0), Vector2(0, 0), Color(0, 0, 255, 100));
						});
				}


				for (Object* object : Objects) {
					if (Control* control = dynamic_cast<Control*>(object))
						control->OnEvent(*e);
				}


				delete e;
			}
			return false;
		}




		~Window() {
			if (window) {
				SDL_DestroyWindow(window);
				window = nullptr;
			}
		}
	};

}
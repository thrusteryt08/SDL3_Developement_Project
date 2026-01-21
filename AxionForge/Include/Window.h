#pragma once
#include "Color.h"
#include "LinkedList.h"
#include "Object.h"
#include "Renderer.h"
#include "Control.h"
namespace AxionForge {

	// Represents a window in the Axion Forge framework
	// Manages rendering, events, and contained objects
	// Uses SDL for window management and rendering
	class Window {
	private:
		// SDL window instance
		SDL_Window* window = nullptr;
		// Background color of the window
		Color backgroundcolor = ColorName::White;

		// Window dimensions and scale
		int Width = 500;
		int Height = 500;
		float Scale = 1.0f;

		bool shouldBakeRender = true;

		// Drag selection variables
		bool isDragSelectingEnabled = false;
		bool isDragSelecting = false;
		Vector2 dragSelectStart;
		ColorRect dragSelectRect;

		Control* focusedControl = nullptr;

		// Disable copy and move semantics
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(Window&&) = delete;
		unsigned int ObjectCount;
	public:
		// Renderer instance for drawing
		Renderer renderer;
		// List of objects contained in the window
		Array<Object*> Objects;

		Window() = default;
		// Create a window with specified title and dimensions
		Window(const char* title, int width, int height) {
			Create(title, width, height);
			//temporary for testing
			Objects.Add(&dragSelectRect);


			BakeRender();
		}
		// Create or recreate the window
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
		// Getters and setters for background color
		void setBackgroundColor(Color color) {
			backgroundcolor = color;
		}
		Color getBackgroundColor() const {
			return backgroundcolor;
		}

		// Getters and setters for window size
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

		// Getters and setters for scale
		float getScale() const {
			return Scale;
		}
		void setScale(float x) {
			Scale = x;
			renderer.setScale(Scale);
		}

		// Delay functions
		void Delay(int x) {
			SDL_Delay(x);
		}
		void DelayNS(int x) {
			SDL_DelayNS(x);
		}

		// Render all objects in the window
		void RenderObjects() {
			for (Object* object : Objects) {
				if (object && object->isShown())
					object->Render(&renderer);
			}
		}

		// Set vertical synchronization
		void setVSync(int x) {
			renderer.SetVSync(x);
		}

		void BakeRender() {
			renderer.setDrawColor(backgroundcolor);
			renderer.Clear();
			RenderObjects();
		}
		// returns true if renderer had to bake
		bool Render() {
			if(shouldBakeRender) {
				shouldBakeRender = false;
				BakeRender();
				renderer.Present();
				return true;
			}
			return false;
		}

		bool HandleEvents(Event& e) {

			if (ObjectCount != Objects.Length()) {
				shouldBakeRender = true;
				ObjectCount = Objects.Length();
			}

			EventDispatcher d(e);

			d.Dispatch<QuitEvent>([this](QuitEvent& ev) {
				return true;
				});
			if (e.Handled)
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

					for (Object* object : Objects) {

					}

					return true;
					});
			}

			if(focusedControl)
				if (!focusedControl->wantsFocus) {
					focusedControl->UnFocus();
					focusedControl = nullptr;
				}

			if (e.Handled)
				return false;

			for (Object* object : Objects) {
				if (Control * control = dynamic_cast<Control*>(object)) {
					if (control->wantsFocus) {
						if (!focusedControl) {
							focusedControl = control;
							control->Focus();
						}
					}
					if(control->OnEvent(e))
						shouldBakeRender = true;
				}
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
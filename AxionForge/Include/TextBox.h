#pragma once
#include "Control.h"
#include "Renderer.h"
#include "Event.h"
#include "ColorRect.h"

namespace AxionForge {

	class TextBox : public Control {
		using string = std::string;
	public:
		Vector2 size = Vector2(200, 30);

		Color backColor = ColorName::Gray;
		Color fontColor = ColorName::Black;

		string Text = "";
		string placeHolderText;
		char flashChar = '|';

		TextBox() {}

		TextBox(Vector2 position) {
			this->position = position;
		}

		TextBox(Vector2 position, string text) {
			this->position = position;
			Text = text;
		}

		TextBox(string text) : Text(text) {}

		bool hasTextInput = false;

		void RequestStartTextInput(SDL_Window* window) {
			hasTextInput = true;
			SDL_StartTextInput(window);
		}

		void RequestStopTextInput(SDL_Window* window) {
			SDL_StopTextInput(window);
			hasTextInput = false;
		}

		void Focus() override {
			Control::Focus();
			RequestStartTextInput(SDL_GetKeyboardFocus());
		}

		void UnFocus() override {
			Control::UnFocus();
			RequestStopTextInput(SDL_GetKeyboardFocus());
		}

		bool OnEvent(Event& e) override {
			EventDispatcher d(e);

			d.Dispatch<MouseButtonDownEvent>([this](MouseButtonDownEvent& ev) {
				if (isColliding(ev.Position))
					wantsFocus = true;
				else
					wantsFocus = false;

				return true;
				});
			d.Dispatch<KeyDownEvent>([this](KeyDownEvent& ev) {
				if (!isFocused) return false;
				
				if (ev.KeyCode == SDLK_BACKSPACE) {
					if (!Text.empty())
						Text.pop_back();
					return true;
				}

				return true;
				});
			d.Dispatch<TextInputEvent>([this](TextInputEvent& ev) {
				if (!isFocused) return false;

				Text += ev.Text;
				return true;
				});
			if (e.Handled)
				return true;
			return false;
		}


		bool isColliding(Vector2 point) const override {
			return Rect(position, size).isColliding(point);
		}
		void Render(Renderer* renderer) override {
			renderer->RenderColorRect(ColorRect(position, size, backColor));
			renderer->setDrawColor(fontColor);
			SDL_RenderDebugText(renderer->Instance(), position.x, position.y, Text.c_str());
		}
	};

}
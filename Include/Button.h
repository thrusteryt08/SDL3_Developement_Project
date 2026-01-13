#pragma once
#include "Control.h"
#include "Event.h"
#include "Renderer.h"
#include "Console.h"
#include "Rect.h"


namespace AxionForge {

	enum class ButtonState : Uint8 {
		Disabled = 0,
		None,
		Hover,
		Pressed
	};

	class Button : public Control {
		using Method = void(*)(Control& sender, Event& event);

		ButtonState state = ButtonState::None;
		bool isStateChanged = false;

	public:
		Vector2 size;

		Color FontColor = ColorName::Black;
		Color BackColor = Color(200, 200, 200);;

		std::string Text = "";


		Button() {
			size = Vector2(100, 50);
		}

		Button(std::string text) : Button() {
			Text = text;
		}

		Rect getArea() const {
			return Rect(position, size);
		}

		bool isColliding(Vector2 point) const override {
			return getArea().isColliding(point);
		}

		Method onClick;
		Method onRightClick;
		Method onEnter;
		Method onLeave;
		Method onPress;
		Method onRelease;

		void OnEvent(Event& e) override {
			EventDispatcher d(e);

			d.Dispatch<MouseMoveEvent>([this](MouseMoveEvent& ev) {
				bool inside = isColliding(ev.Position);

				if (inside && state == ButtonState::None) {
					state = ButtonState::Hover;
					if (onEnter) onEnter(*this, ev);
				}
				else if (!inside && state == ButtonState::Hover) {
					state = ButtonState::None;
					if (onLeave) onLeave(*this, ev);
				}
				return false;
				});

			d.Dispatch<MouseButtonDownEvent>([this](MouseButtonDownEvent& ev) {
				if (state == ButtonState::Hover && ev.Button == 1) {
					state = ButtonState::Pressed;
					if (onPress) onPress(*this, ev);
					return true;
				}
				return false;
				});

			d.Dispatch<MouseButtonUpEvent>([this](MouseButtonUpEvent& ev) {
				if (state == ButtonState::Pressed && ev.Button == 1) {

					bool inside = isColliding(ev.Position);
					state = inside ? ButtonState::Hover : ButtonState::None;
					if (inside && onClick) onClick(*this, ev);
					if (onRelease) onRelease(*this, ev);
					return true;
				}
				return false;
				});
		}

		void Render(Renderer* renderer) override {
			renderer->RenderFillRect(ColorRect(position, size, BackColor));
			renderer->setDrawColor(FontColor);
			SDL_RenderDebugText(renderer->Instance(), position.x, position.y, &Text[0]);
		}
		
		std::string ToString() override {
			return "Button";
		}

		~Button() {

		}

	};

	


}
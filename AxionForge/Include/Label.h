#pragma once
#include "Event.h"
#include "Color.h"
#include "Rect.h"
#include "Control.h"

namespace AxionForge {

	class Label : public Control {
	public:
		Vector2 size;


		Color FontColor = ColorName::Black;
		Color BackColor = ColorName::Gray;

		std::string Text = "";



		Label() {
			position = Vector2(0);
			size = Vector2(100);
		}
		Label(std::string text) : Label() {
			Text = text;
		}
		Rect getArea() const {
			return Rect(position, size);
		}

		bool isColliding(Vector2 point) const override {
			return getArea().isColliding(point);
		}

		void Render(Renderer* renderer) override {
			renderer->RenderColorRect(ColorRect(position, size, BackColor));
			renderer->setDrawColor(FontColor);
			SDL_RenderDebugText(renderer->Instance(), position.x, position.y, &Text[0]);
		}

		std::string ToString()override {
			return "Label";
		}
	};
}
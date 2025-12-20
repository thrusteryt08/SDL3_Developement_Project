#include "Objects/ColorRect.h"

namespace AxionForge {

	ColorRect::ColorRect(Vector2 Origin, Vector2 Size) {
		position = Origin;
		size = Size;
	}
	ColorRect::ColorRect(Vector2 Origin, Vector2 Size, Color color) {
		position = Origin;
		size = Size;
		this->color = color;
	}
	ColorRect::ColorRect(Vector2 Origin, Vector2 Size, Color color, Opacity opacity) {
		position = Origin;
		size = Size;
		this->color = color;
		this->opacity = opacity;
	}
	void ColorRect::setColor(Color color) {
		this->color = color;
	}
	void ColorRect::setColor(Color color, Opacity opacity) {
		this->color = color;
		this->opacity = opacity;
	}
	void ColorRect::Render(Renderer* renderer) {
		renderer->RenderFillRect(position, size, color);
	}

}
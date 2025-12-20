#include "../Include/Objects/Point.h"

namespace AxionForge {

	Point::Point(Vector2 position, Color color) {
		this->position = position;
		this->color = color;
	}

	void Point::Render(Renderer* renderer) {
		renderer->RenderPoint(position, color);
	}

}
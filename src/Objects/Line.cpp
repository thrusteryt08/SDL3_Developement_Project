#include "../Include/Objects/Line.h"

namespace AxionForge {

	Line::Line(Vector2 position, Vector2 end, Color color) {
		this->position = position;
		this->end = end;
		this->color = color;
	}

	void Line::Render(Renderer* renderer) {
		renderer->RenderLine(position, end, color);
	}

}
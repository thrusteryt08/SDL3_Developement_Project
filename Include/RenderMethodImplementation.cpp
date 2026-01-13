#pragma once
#include "Renderer.h"
#include "Includes/Objects.h"

namespace AxionForge {

	void Object::Render(Renderer* renderer) { }

	void Point::Render(Renderer* renderer) {
		renderer->RenderPoint(*this);
	}

	void Line::Render(Renderer* renderer) {
		renderer->RenderLine(*this);
	}

	void ColorRect::Render(Renderer* renderer) {
		renderer->RenderFillRect(*this);
	}

}

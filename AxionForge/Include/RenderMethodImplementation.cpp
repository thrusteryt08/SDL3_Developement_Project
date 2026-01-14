#pragma once
#include "Renderer.h"
#include "Object.h"
#include "Point.h"
#include "Line.h"
#include "ColorRect.h"


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

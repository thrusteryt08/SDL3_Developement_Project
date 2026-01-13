#pragma once
#include "Object.h"
#include "Color.h"

namespace AxionForge {

	class Line : public Object {
	public:
		Vector2 end;
		Color color;

		Line() = default;
		Line(Vector2 position, Vector2 end) {
			this->position = position;
			this->end = end;
		}
		Line(Vector2 position, Vector2 end, Color color) {
			this->position = position;
			this->end = end;
			this->color = color;
		}
		
		void Render(Renderer* renderer) override;
	};

}
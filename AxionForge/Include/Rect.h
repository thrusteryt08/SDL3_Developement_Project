#pragma once
#include "Object.h"

namespace AxionForge {

	class Rect : public Object {
	public:
		Vector2 size;

		Rect() = default;
		Rect(Vector2 Origin, Vector2 Size) {
			position = Origin;
			size = Size;
		}

		bool isColliding(const Vector2& point) const {
			return point >= position && point <= position + size;
		}

		bool isColliding(const Rect& rect) const {
			return !(position + size <= rect.position ||
				position >= rect.position + rect.size);
		}

		void Render(Renderer* renderer) override {

		}
	};

}
#include "Object.h"
#include "Color.h"
#include "Renderer.h"

namespace AxionForge {

	class Point : public Object {
	public:
		Color color;

		Point() = default;
		Point(Vector2 position, Color color = ColorName::Black) {
			this->position = position;
			this->color = color;
		}

		void Render(Renderer* renderer) override;
	};

}
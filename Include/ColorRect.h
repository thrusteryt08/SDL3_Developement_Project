#include "Rect.h"
#include "Color.h"
#include "Renderer.h"

namespace AxionForge {

	class ColorRect : public Rect {
	public:
		Color color;

		ColorRect() = default;
		ColorRect(Vector2 position, Vector2 size) : Rect(position, size) { }
		ColorRect(Vector2 position, Vector2 size, Color color) : ColorRect(position, size) {
			this->color = color;
		}

		void Render(Renderer* renderer) override;
	};

}
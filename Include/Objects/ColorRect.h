#include "Objects/Object.h"

namespace AxionForge {

	class ColorRect : public Object {
	public:
		Color color;
		Opacity opacity = OpacityLevel::Opaque;
		ColorRect() = default;
		ColorRect(Vector2 Origin, Vector2 Size);
		ColorRect(Vector2 Origin, Vector2 Size, Color color);
		ColorRect(Vector2 Origin, Vector2 Size, Color color, Opacity opacity);
		void setColor(Color color);
		void setColor(Color color, Opacity opacity);
		void Render(Renderer* renderer) override;
	};

}
#include "Objects/Object.h"
#include "Graphics/Color.h"

namespace AxionForge {

	class Point : public Object {
	public:
		Color color;
		Point() = default;
		Point(Vector2 position, Color color = ColorName::Black);
		void Render(Renderer* renderer) override;
	};

}
#include "Objects/Object.h"
#include "../Include/Graphics/Color.h"

namespace AxionForge {

	class Line : public Object {
	public:
		Vector2 end;
		Color color;
		Line() = default;
		Line(Vector2 position, Vector2 end, Color color = ColorName::Black);
		void Render(Renderer* renderer) override;
	};

}
#include "Objects/Object.h"

namespace AxionForge {
	
	class Rect : public Object {
	public:
		Rect() = default;
		Rect(Vector2 Origin, Vector2 Size);
		void Render(Renderer* renderer) override;
	};

}
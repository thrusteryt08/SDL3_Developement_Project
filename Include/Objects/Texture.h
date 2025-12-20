#include "Object.h"
#include "../Include/Graphics/Renderer.h"

namespace AxionForge {

	class Texture : public Object {
		SDL_Texture* texture = nullptr;

	public:
		Texture() = default;

		~Texture();

	};

}
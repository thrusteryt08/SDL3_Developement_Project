#pragma once
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_pixels.h"

namespace AxionForge {

	enum class OpacityLevel : Uint8 {
		Transparent = SDL_ALPHA_TRANSPARENT,
		Opaque = SDL_ALPHA_OPAQUE
	};
	enum class OpacityLevelFloat {
		Transparent = (int)SDL_ALPHA_TRANSPARENT_FLOAT,
		Opaque = (int)SDL_ALPHA_OPAQUE_FLOAT
	};
	
	class Opacity {
	public:
		Uint8 alpha = static_cast<Uint8>(OpacityLevel::Opaque);

		Opacity() = default;
		Opacity(Uint8 alpha) { this->alpha = alpha; }
		Opacity(OpacityLevel level) { this->alpha = static_cast<Uint8>(level); }
	};

}
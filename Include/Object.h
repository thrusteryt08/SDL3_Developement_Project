#pragma once
#include "Vector2.h"

namespace AxionForge {

	class Renderer;

	class Object {
	protected:
		bool isRendering = true;

	public:
		Vector2 position;

		Object() = default;
		Object(Vector2 position) { position = position; }

		void Show() { isRendering = true; }
		void Hide() { isRendering = false; }
		bool isShown() const { return isRendering; }

		virtual void Render(Renderer* renderer);

		virtual ~Object() = default;
	};

}
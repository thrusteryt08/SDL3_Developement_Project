#pragma once
#include <SDL3/SDL_render.h>
#include "Color.h"
#include "Vector2.h"
#include "Point.h"
#include "Line.h"
#include "ColorRect.h"
#include "Rect.h"
#include "Object.h"

namespace AxionForge {

	// Renderer class for handling rendering operations
	// Wraps SDL_Renderer and provides methods for drawing shapes and objects
	class Renderer {
	private:
		SDL_Renderer* renderer = nullptr;

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
	public:
		Renderer() = default;
	   
		SDL_Renderer** InstanceAddress() { return &renderer; }
		SDL_Renderer* Instance() const { return renderer; }

		// Clears the current rendering target
		void Clear() { SDL_RenderClear(renderer); }
		// Presents the rendered content to the screen
		void Present() { SDL_RenderPresent(renderer); }
		// Set vertical synchronization
		void SetVSync(int x) { SDL_SetRenderVSync(renderer, x); }

		// Setters for draw color
		void setDrawColor(Color color, Opacity opacity = OpacityLevel::Opaque) {
			SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, opacity.alpha);
		}

		// Setters for scale
		void setScale(float scale) {
			SDL_SetRenderScale(renderer, scale, scale);
		}
		void setScale(float scaleX, float scaleY) {
			SDL_SetRenderScale(renderer, scaleX, scaleY);
		}

		void RenderObject(Object* object) {
			if (object)
				object->Render(this);
		}

		void RenderPoint(const Point& point) {
			setDrawColor(point.color);
			SDL_RenderPoint(renderer, point.position.x, point.position.y);
		}
		void RenderLine(const Line& line) {
			setDrawColor(line.color);
			SDL_RenderLine(renderer, line.position.x, line.position.y, line.end.x, line.end.y);
		}
		void RenderRect(const Rect& rect) {
			SDL_FRect r{ rect.position.x, rect.position.y, rect.size.x, rect.size.y };
			SDL_RenderRect(renderer, &r);
		}
		void RenderColorRect(const ColorRect& cRect) {
			setDrawColor(cRect.color);
			SDL_FRect r{ cRect.position.x, cRect.position.y, cRect.size.x, cRect.size.y };
			SDL_RenderFillRect(renderer, &r);
		}
		
		~Renderer() {
			if (renderer) {
				SDL_DestroyRenderer(renderer);
				renderer = nullptr;
			}
		}
	};

}
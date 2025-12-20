#include "Graphics/Renderer.h"
#include "Objects/Object.h"

namespace AxionForge {

    Renderer::~Renderer() {
        SDL_DestroyRenderer(renderer);
    }

    SDL_Renderer** Renderer::InstanceAddress() { return &renderer; }
    SDL_Renderer* Renderer::Instance() { return renderer; }

    void Renderer::Clear() { SDL_RenderClear(renderer); }
    void Renderer::Present() { SDL_RenderPresent(renderer); }
    void Renderer::Delay(int ms) { SDL_Delay(ms); }

    void Renderer::SetVSync(int x) {
        SDL_SetRenderVSync(renderer, x);
	}

    void Renderer::setDrawColor(Color c, Opacity o) {
        SDL_SetRenderDrawColor(renderer, c.red, c.green, c.blue, o.alpha);
    }

    void Renderer::setScale(float s) {
        SDL_SetRenderScale(renderer, s, s);
    }

    void Renderer::RenderObject(Object* object) {
        object->Render(this);
    }

    void Renderer::RenderPoint(Vector2 p, Color c) {
        setDrawColor(c);
        SDL_RenderPoint(renderer, p.x, p.y);
    }

    void Renderer::RenderLine(Vector2 a, Vector2 b, Color c) {
        setDrawColor(c);
        SDL_RenderLine(renderer, a.x, a.y, b.x, b.y);
    }

    void Renderer::RenderFillRect(Vector2 pos, Vector2 size, Color c) {
        setDrawColor(c);
        SDL_FRect r{ pos.x, pos.y, size.x, size.y };
        SDL_RenderFillRect(renderer, &r);
    }

    void Renderer::RenderCircle(float radius, Vector2 center, Color c) {
        setDrawColor(c);
        float x = radius, y = 0, err = 0;

        while (x >= y) {
            SDL_RenderPoint(renderer, center.x + x, center.y + y);
            SDL_RenderPoint(renderer, center.x + y, center.y + x);
            SDL_RenderPoint(renderer, center.x - y, center.y + x);
            SDL_RenderPoint(renderer, center.x - x, center.y + y);
            SDL_RenderPoint(renderer, center.x - x, center.y - y);
            SDL_RenderPoint(renderer, center.x - y, center.y - x);
            SDL_RenderPoint(renderer, center.x + y, center.y - x);
            SDL_RenderPoint(renderer, center.x + x, center.y - y);

            if (err <= 0) err += 2 * ++y + 1;
            if (err > 0)  err -= 2 * --x + 1;
        }
    }

}
#pragma once
#include <SDL3/SDL.h>
#include "../Graphics/Color.h"
#include "../Core/Vector2.h"

namespace AxionForge {

    class Object;

    class Renderer {
        SDL_Renderer* renderer = nullptr;

    public:
        Renderer() = default;
        ~Renderer();

        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;

        SDL_Renderer** InstanceAddress();
        SDL_Renderer* Instance();

        void Clear();
        void Present();
        void Delay(int ms);

        void setDrawColor(Color color, Opacity opacity = OpacityLevel::Opaque);
        void setScale(float s);

        void RenderObject(Object* obj);

        void RenderPoint(Vector2 p, Color c);
        void RenderLine(Vector2 a, Vector2 b, Color c);
        void RenderFillRect(Vector2 pos, Vector2 size, Color c);
        void RenderCircle(float radius, Vector2 center, Color c);
    };

}
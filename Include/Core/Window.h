#pragma once

#include "Graphics/Renderer.h"
#include "Graphics/Color.h"
#include "Objects/Object.h"
#include "../Core/DataStructures/Vector.h"
#include "Vector2.h"

namespace AxionForge {

    class Window {
    private:
        SDL_Window* window = nullptr;
        Color backgroundcolor = ColorName::White;

    public:
        int Width = 500;
        int Height = 500;
        float Scale = 1.0f;
        Uint32 Delay = 0;

        Renderer renderer;
        Vector<Object*> Objects;

        Window();
        Window(const char* title, int width, int height);

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;

        void Create(const char* title, int width, int height);

        void setBackgroundColor(Color color);

        void Resize(Vector2 size);
        void Resize(int x, int y);

        void setScale(float x);
        void setDelay(int x);

        void RenderObjects();
        void Render();

        ~Window();
    };

}
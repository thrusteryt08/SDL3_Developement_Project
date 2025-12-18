#pragma once
#include "../Core/Vector2.h"

namespace AxionForge {

    class Renderer;

    class Object {
    protected:
        bool isRendering = true;

    public:
        Vector2 position{};
        Vector2 size{};

        Object() = default;
        Object(Vector2 position, Vector2 size);

        void Show();
        void Hide();
        bool isShown() const;

        virtual void Render(Renderer* renderer) = 0;
        virtual ~Object() = default;
    };

}
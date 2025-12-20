#include "../Include/Objects/Object.h"

namespace AxionForge {

    Object::Object(Vector2 position, Vector2 size) {
        this->position = position;
        this->size = size;
    }

    void Object::Show() { isRendering = true; }
    void Object::Hide() { isRendering = false; }
    bool Object::isShown() const { return isRendering; }

}
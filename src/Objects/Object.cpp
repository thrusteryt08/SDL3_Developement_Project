#include "../Include/Objects/Object.h"

namespace AxionForge {

    Object::Object(Vector2 pos, Vector2 sz)
        : position(pos), size(sz) {
    }

    void Object::Show() { isRendering = true; }
    void Object::Hide() { isRendering = false; }
    bool Object::isShown() const { return isRendering; }

}
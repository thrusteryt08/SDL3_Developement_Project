#pragma once
#include "../Core/Enums.h"

namespace AxionForge {

    class Opacity {
    public:
        Uint8 alpha = static_cast<Uint8>(OpacityLevel::Opaque);

        Opacity() = default;
        Opacity(Uint8 alpha) { this->alpha = alpha; }
        Opacity(OpacityLevel level) { this->alpha = static_cast<Uint8>(level); }
    };

}
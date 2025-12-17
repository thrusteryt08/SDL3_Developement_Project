#pragma once

namespace AxionForge {

    // Base class for static-only classes
    class Static_Class {
    protected:
        Static_Class() {}
        Static_Class(const Static_Class&) = delete;
        Static_Class& operator=(const Static_Class&) = delete;
    };

}
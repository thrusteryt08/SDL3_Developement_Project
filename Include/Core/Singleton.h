#pragma once

namespace AxionForge {

    // Base class for singletons
    class Singleton {
    protected:
        Singleton() {}
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
    };

}
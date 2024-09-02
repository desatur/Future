#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Core.hpp"
#include "Window/Window.hpp"
#include "Rendering/BackendWrapper.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Future {
    class FE_API Engine {
    public:
        void Run();
    };

    // Client:
    Engine* CreateApplication();
}

#endif // ENGINE_HPP
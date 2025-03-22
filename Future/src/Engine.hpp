#pragma once
#include "Core.hpp"
#include "Window/Window.hpp"
#include "Rendering/Renderer.hpp"
#define STB_IMAGE_IMPLEMENTATION
#define GLM_ENABLE_EXPERIMENTAL
#include <stb_image.h>
#include "Window/Window.hpp"
#include "Rendering/Renderer.hpp"

namespace Future {
    class FE_API Engine {
    public:
        void Run();
    };

    // Client:
    Engine* CreateApplication();
}
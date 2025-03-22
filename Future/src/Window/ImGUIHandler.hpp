#pragma once
#include "Window.hpp"
#include "../Rendering/Renderer.hpp"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include "../Log.hpp"

namespace Future
{
    class ImGUIHandler {
        public:
        ImGUIHandler(Window* window);
        ~ImGUIHandler();

        void NewFrame();
        void DrawFrame();
        void DebugWindow();
        private:

    };
}

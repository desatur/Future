#pragma once
#include "Window.hpp"

namespace Future
{
    class ImGUIHandler {
        public:
        ImGUIHandler(Window* window);
        ~ImGUIHandler();

        void NewFrame();
        void DrawFrame();
        private:

    };
}

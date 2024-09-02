#include "Engine.hpp"
#include "Window/Window.hpp"
#include "Rendering/OpenGL/OpenGL.hpp"

namespace Future {
    void Engine::Run() {
        auto window = new Future::Window();
        window->Init();
        auto renderer = new Future::OpenGL(window);
        renderer->Init();
        //window->Init();
        //window->Loop();
    }
}

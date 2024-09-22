#include "Engine.hpp"
#include "Window/Window.hpp"
#include "Rendering/Renderer.hpp"

namespace Future {
    void Engine::Run() {
        auto window = new Future::Window();
        window->Init();
        auto renderer = new Future::Renderer(window);
        renderer->Init();
        //window->Init();
        //window->Loop();
    }
}

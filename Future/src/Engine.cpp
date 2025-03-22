#include "Engine.hpp"

namespace Future {
    void Engine::Run() {
        auto window = new Future::Window();
        window->Init();
        auto renderer = new Future::Renderer(window);
        renderer->Init();
    }
}

#include "Engine.hpp"
#include "Window/Window.hpp"
#include "Rendering/BackendWrapper.hpp"

namespace Future {
    void Engine::Run() {
        auto window = new Future::Window();
        window->Init();
        auto renderer = new Future::BackendWrapper(window, static_cast<Backend>(0x01));
        renderer->Init();
        //window->Init();
        //window->Loop();
    }
}

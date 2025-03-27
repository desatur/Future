#include "Core.hpp"
#include "Log/Log.hpp"
#include "../../Rendering/src/Window/PresentationWindow.hpp"

namespace Future {
    Core::Core()
    {
    }
    
    Core::~Core()
    {
    }

    void Core::Run()
    {
        PresentationWindow window(1920, 1080, "nullge");
        Loop();
    }

    void Core::Loop(){
        LOG_INFO("Main Core Loop Started.");
        while (true){
            PresentationWindow::PollWindowEvents();
        }
    }
}


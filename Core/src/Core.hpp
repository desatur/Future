#pragma once
#include "Export.hpp"

namespace Future {
    class FUTURE_API Core {
        public:
            Core();
            virtual ~Core();
            void Run();
            void Loop();
        };
        
        Core* CreateApplication();
}

#include "../../Core/Core.hpp"

class Sandbox : public Future::Core {
    public:
        Sandbox() {
    
        }
        ~Sandbox() {
        }
    };

Future::Core* CreateApplication() {
    return new Sandbox();
}

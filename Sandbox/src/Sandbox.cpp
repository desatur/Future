#include "../../Core/src/Core.hpp"

class Sandbox : public Core {
    public:
        Sandbox() {
    
        }
        ~Sandbox() {
        }
    };
    
    Core* CreateApplication() {
        return new Sandbox;
    }
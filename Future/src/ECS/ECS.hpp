#pragma once
#include "Objects/ObjectManager.hpp"
#include "Components/ComponentManager.hpp"

namespace Future {
    class ECS {
    public:
        ECS();
        ~ECS();

    private:
        std::unique_ptr<ObjectManager> entityManager;
        std::unique_ptr<ComponentManager> componentManager;
    };
}

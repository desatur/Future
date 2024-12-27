#pragma once
#include "DrawRequest.hpp"
#include <glad.h>

namespace Future {
    class DrawLayerHandler {
        public:

        private:
            std::vector<DrawRequest> drawRequestQueue;
    };
}
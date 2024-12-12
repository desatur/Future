#pragma once
#include "DrawRequest.hpp"
#include <glad.h>

namespace Future {
    class DrawCallHandler {
        public:
            [[nodiscard]] unsigned int GetDrawCalls() const { return drawRequestQueue.size(); }
            unsigned int Push(DrawRequest request);
            bool Pop(unsigned int ID);
            void DrawFrame();

        private:
            std::vector<DrawRequest> drawRequestQueue;
    };
}
#pragma once
#include <glad/glad.h>
#include "vec2.hpp"
#include "vec3.hpp"

namespace Future {
    class RectangleVBO {
        public:
            GLuint ID;
            RectangleVBO();

            void Bind();
            void Unbind();
            void Delete();
    };
};
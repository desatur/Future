#pragma once
#include <iostream>
#include <glad/glad.h>
#include <stb_image.h>
#include "../../Log.hpp"
#include "../Shaders/Shaders.hpp"
#include "TexType.hpp"

namespace Future
{
    class Texture {
        public:
            GLuint ID;
            TexType type;
            GLuint unit;
            Texture(const char* image, TexType texType, GLuint slot);

            void texUnit(Shaders& shader, const char* uniform, GLuint unit);
            void Bind();
            void Unbind();
            void Delete();
    };
}
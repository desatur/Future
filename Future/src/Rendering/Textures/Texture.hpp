#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <iostream>
#include <glad/glad.h>
#include <stb_image.h>
#include "../../Log.hpp"
#include "../Shaders.hpp"

namespace Future
{
    class Texture {
        public:
            GLuint ID;
            const char* type;
            GLuint unit;
            Texture(const char* image, const char* texType, GLuint slot);

            void texUnit(Shaders& shader, const char* uniform, GLuint unit);
            void Bind();
            void Unbind();
            void Delete();
    };
}

#endif //TEXTURE_HPP

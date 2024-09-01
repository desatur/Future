#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <stb_image.h>

#include "../Shaders.hpp"

namespace Future
{
    class Texture {
        public:
            GLuint ID;
            const char* type;
            GLuint unit;
            Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType);

            void texUnit(Shaders& shader, const char* uniform, GLuint unit);
            void Bind();
            void Unbind();
            void Delete();
    };
}

#endif //TEXTURE_HPP

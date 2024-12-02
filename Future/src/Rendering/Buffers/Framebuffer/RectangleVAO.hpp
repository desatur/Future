#ifndef RECTANGLEVAO_HPP
#define RECTANGLEVAO_HPP
#include <glad/glad.h>
#include "RectangleVBO.hpp"

namespace Future
{
    class RectangleVAO
    {
        public:
            GLuint ID;
            RectangleVAO();

            void LinkAttrib(RectangleVBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
            void Bind();
            void Unbind();
            void Delete();
    };
}

#endif //VAO_HPP

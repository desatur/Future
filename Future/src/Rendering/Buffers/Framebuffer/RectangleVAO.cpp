#include "RectangleVAO.hpp"

namespace Future
{
    RectangleVAO::RectangleVAO()
    {
        glGenVertexArrays(1, &ID);
    }

    void RectangleVAO::LinkAttrib(RectangleVBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
    {
        VBO.Bind();
        glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
        VBO.Unbind();
    }

    void RectangleVAO::Bind()
    {
        glBindVertexArray(ID);
    }

    void RectangleVAO::Unbind()
    {
        glBindVertexArray(0);
    }

    void RectangleVAO::Delete()
    {
        glDeleteVertexArrays(1, &ID);
    }
}
#include "RectangleVBO.hpp"

namespace Future
{
    RectangleVBO::RectangleVBO()
    {
        float rectangleVertices[] = {
            // Coords    // texCoords
            -1.0f, -1.0f,  0.0f, 0.0f, // First triangle
            1.0f, -1.0f,  1.0f, 0.0f,
            -1.0f,  1.0f,  0.0f, 1.0f,

            1.0f, -1.0f,  1.0f, 0.0f, // Second triangle
            1.0f,  1.0f,  1.0f, 1.0f,
            -1.0f,  1.0f,  0.0f, 1.0f
        };

        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
    }

    void RectangleVBO::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    void RectangleVBO::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void RectangleVBO::Delete()
    {
        glDeleteBuffers(1, &ID);
    }
}

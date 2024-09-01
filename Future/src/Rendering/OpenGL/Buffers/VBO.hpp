#ifndef VBO_HPP
#define VBO_HPP
#include <glad/glad.h>

namespace Future
{
    class VBO
    {
        public:
            // Reference ID of the Vertex Buffer Object
            GLuint ID;
            // Constructor that generates a Vertex Buffer Object and links it to vertices
            VBO(GLfloat* vertices, GLsizeiptr size);

            void Bind();
            void Unbind();
            void Delete();
    };
};

#endif //VBO_HPP

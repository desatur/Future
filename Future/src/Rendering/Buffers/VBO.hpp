#ifndef VBO_HPP
#define VBO_HPP
#include <glad/glad.h>

#include "vec2.hpp"
#include "vec3.hpp"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 color;
    glm::vec2 TexCoords;
};

namespace Future
{
    class VBO
    {
        public:
            // Reference ID of the Vertex Buffer Object
            GLuint ID;
            // Constructor that generates a Vertex Buffer Object and links it to vertices
            VBO(std::vector<Vertex>& vertices);

            void Bind();
            void Unbind();
            void Delete();
    };
};

#endif //VBO_HPP

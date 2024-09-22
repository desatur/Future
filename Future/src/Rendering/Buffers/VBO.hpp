#ifndef VBO_HPP
#define VBO_HPP
#include <glad/glad.h>

#include "vec2.hpp"
#include "vec3.hpp"
#include "../Vertex.hpp"

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

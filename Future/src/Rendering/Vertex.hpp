#ifndef VERTEX_HPP
#define VERTEX_HPP
#include "vec2.hpp"
#include "vec3.hpp"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 color;
    glm::vec2 TexCoords;
};

#endif //VERTEX_HPP

#pragma once
#include "vec2.hpp"
#include "vec3.hpp"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 color;
    glm::vec2 TexCoords;
};

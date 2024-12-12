#pragma once
#include "../Shaders.hpp"
#include "../Mesh/Mesh.hpp"

struct DrawRequest
{
    unsigned int ID;
    Future::Shaders shaders;
    //Future::Material material;
    Future::Mesh mesh;
    glm::mat4 modelMatrix;
};

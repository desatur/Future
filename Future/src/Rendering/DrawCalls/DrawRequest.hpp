#pragma once
#include "../Shaders/Shaders.hpp"
#include "../Mesh/Mesh.hpp"

struct DrawRequest
{
    Future::Shaders shaders;
    //Future::Material material;
    Future::Mesh mesh;
    glm::mat4 modelMatrix;
};

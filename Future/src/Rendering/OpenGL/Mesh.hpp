#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include "Buffers/VAO.hpp"
#include "Buffers/EBO.hpp""
#include "Camera.hpp"
#include "Textures/Texture.hpp"

namespace Future
{
    class Mesh
    {
        public:
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;

        VAO VAO;

        Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector<Texture>& textures);

        void Draw(Shaders& shaders, Camera& camera);
    };
}

#endif //MESH_HPP

#ifndef MESH_HPP
#define MESH_HPP

#include <string>
#include <vector>

#include "../Buffers/VAO.hpp"
#include "../Buffers/EBO.hpp"
#include "../Camera.hpp"
#include "../Textures/Texture.hpp"

namespace Future
{
    class Mesh
    {
        public:
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;
        Mesh(std::vector <Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Draw(Shaders &shader);

        private:
        Future::VAO VAO;
        Future::VBO VBO;
        Future::EBO EBO;
        void SetupMesh();
    };
}

#endif //MESH_HPP

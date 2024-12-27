#pragma once
#include <string>
#include <vector>
#include "../Buffers/VAO.hpp"
#include "../Buffers/EBO.hpp"
#include "../Camera.hpp"
#include "../Textures/Texture.hpp"
#include "../Textures/TexType.hpp"
#include "../Textures/TexTypeHelpers.hpp"
// TODO: Move Renderer/Buffers to this dir

namespace Future
{
    class Mesh
    {
        public:
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;
        Mesh(std::vector <Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Draw(Shaders &shader, Camera &camera, glm::mat4 matrix, glm::vec3 translation, glm::quat rotation, glm::vec3 scale);

        private:
        Future::VAO VAO;
        Future::VBO VBO;
        Future::EBO EBO;
        void SetupMesh();
    };
}

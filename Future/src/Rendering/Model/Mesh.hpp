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

        VAO VAO;

        Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector<Texture>& textures);

        void Draw
        (
            Shaders& shader,
            Camera& camera,
            glm::mat4 matrix = glm::mat4(1.0f),
            glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
            glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
            glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
        );
        private:
        void SetupMesh();
    };
}

#endif //MESH_HPP

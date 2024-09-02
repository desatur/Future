#ifndef MODEL_HPP
#define MODEL_HPP

#include <../../../thirdParty/tinygltf/tiny_gltf.h>
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Shaders.hpp"
#include "Buffers/VBO.hpp"
#include "Textures/Texture.hpp"
#include "../Log.hpp"

namespace Future
{
    class Model
    {
    public:
        Model(const char* file);

        void Draw(Shaders& shader, Camera& camera);

    private:
        std::string file;
        tinygltf::Model gltfModel;
        std::vector<Mesh> meshes;
        std::vector<glm::vec3> translationsMeshes;
        std::vector<glm::quat> rotationsMeshes;
        std::vector<glm::vec3> scalesMeshes;
        std::vector<glm::mat4> matricesMeshes;

        std::vector<std::string> loadedTexName;
        std::vector<Texture> loadedTex;

        void loadMesh(unsigned int indMesh);
        void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));
        std::vector<Texture> getTextures();
    };
}

#endif //MODEL_HPP

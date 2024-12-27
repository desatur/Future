#pragma once
#include "../Camera.hpp"
#include "Mesh.hpp"
#include "../Shaders/Shaders.hpp"
#include "../Buffers/VBO.hpp"
#include "../Textures/Texture.hpp"
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/gtx/matrix_decompose.hpp>

namespace Future
{
    class Model
    {
    public:
        Model(const char* file);
        void Draw(Shaders& shader, Camera& camera);
    private:
        std::vector<Mesh> meshes;
        std::vector<glm::vec3> translationsMeshes;
        std::vector<glm::quat> rotationsMeshes;
        std::vector<glm::vec3> scalesMeshes;
        std::vector<glm::mat4> matricesMeshes;
        const char *model_path;
        std::string directory;

        void LoadModel();
        void ProcessNode(const aiNode *node, const aiScene *scene);
        Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type);
        glm::mat4 ConvertMatrixToGLM(const aiMatrix4x4& from);
    };
}
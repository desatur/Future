#ifndef MODEL_HPP
#define MODEL_HPP

#include <../../../thirdParty/json/include/nlohmann/json.hpp>

#include "../Camera.hpp"
#include "Mesh.hpp"
#include "../Shaders.hpp"
#include "../Buffers/VBO.hpp"
#include "../Textures/Texture.hpp"
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Future
{
    class Model
    {
    public:
        Model(const char* file);

        void Draw(Shaders& shader, Camera& camera);
    private:
        // model data
        std::vector<Mesh> meshes;
        char* directory;

        void LoadModel(const char* file);
        void ProcessNode(const aiNode *node, const aiScene *scene);
        Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, char* typeName);
    };
}

#endif //MODEL_HPP
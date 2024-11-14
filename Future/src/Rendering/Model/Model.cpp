#include "Model.hpp"
#include <iostream>

namespace Future
{
    Model::Model(const char *path)
    {
        model_path = path;
        LoadModel();
    }

    void Model::Draw(Shaders& shader, Camera& camera)
    {
        // Go over all meshes and draw each one
        for (unsigned int i = 0; i < meshes.size(); i++)
        {
            meshes[i].Draw(shader);
        }
    }

    void Model::LoadModel()
    {
        Assimp::Importer import;
        const aiScene *scene = import.ReadFile(model_path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << import.GetErrorString() << "\n";
            return;
        }
        std::string path_str = model_path;
        std::string strdirectory = path_str.substr(0, path_str.find_last_of('/'));
        directory = strdirectory.c_str();

        ProcessNode(scene->mRootNode, scene);
    }

    void Model::ProcessNode(const aiNode* node, const aiScene* scene)
    {
        // process all the node's meshes (if any)
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(ProcessMesh(mesh, scene));
        }
        // then do the same for each of its children
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector;

            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;

            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;
            }

            if (mesh->mTextureCoords[0])
            {
                glm::vec2 texCoord;
                texCoord.x = mesh->mTextureCoords[0][i].x;
                texCoord.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = texCoord;
            }
            else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

            // TODO: Make typeName a enum that is a byte to decrease memory usage and increase texture loading
            std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

            std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

            // NOT IMPLEMENTED
            //std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS, "normal");
            //textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        }

        return Mesh(vertices, indices, textures);
    }

    std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
    {
        aiString str;
        std::vector<Texture> textures;
        unsigned int textureCount = mat->GetTextureCount(type);

        for(unsigned int i = 0; i < textureCount; i++)
        {
            mat->GetTexture(type, i, &str);
            std::string texture_path = directory + '/' + std::string(str.C_Str());
            Texture texture(texture_path.c_str(), typeName.c_str(), i);
            textures.push_back(texture);
        }
        return textures;
    }
}

#include "Model.hpp"
#include <iostream>

namespace Future
{
    Model::Model(const char *path)
    {
        model_path = path;
        LoadModel();
    }

    void Model::Draw(Shaders &shader, Camera &camera)
    {
        // Go over all meshes and draw each one
        for (unsigned int i = 0; i < meshes.size(); i++)
        {
            meshes[i].Draw(shader, camera, matricesMeshes[i], translationsMeshes[i], rotationsMeshes[i], scalesMeshes[i]);
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
        // Extract transformation for this node
        aiMatrix4x4 aiTransform = node->mTransformation;
        glm::mat4 transform = ConvertMatrixToGLM(aiTransform);

        glm::vec3 translation, scale, skew;
        glm::quat rotation;
        glm::vec4 perspective;

        glm::decompose(transform, scale, rotation, translation, skew, perspective);

        // Process all the node's meshes (if any)
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(ProcessMesh(mesh, scene));

            // Store transformations for each mesh
            translationsMeshes.push_back(translation);
            rotationsMeshes.push_back(rotation);
            scalesMeshes.push_back(scale);
            matricesMeshes.push_back(transform);
        }

        // Recursively process each of its children
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
            std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

            std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR);
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

            std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_NORMALS);
            textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        }

        for (unsigned int i = 0; i < textures.size(); i++)
        {
            Texture txt = textures[i];
            std::cout << "Texture "<< i << " // ID:" <<  txt.ID << " Type:" << txt.type <<"\n"; // Type is not correct here, doesn't exist (output: Texture 1 // ID:2 Type:) [Type is not printed out] (Fixed in rework)
        }

        return Mesh(vertices, indices, textures);
    }

    std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type)
    {
        const char* texType;
        switch (type)
        {
            case aiTextureType_DIFFUSE:
                texType = "diffuse";
                break;
            case aiTextureType_SPECULAR:
                texType = "specular";
                break;
            case aiTextureType_NORMALS:
                texType = "normal";
                break;
            default:
                break;
        }

        aiString str;
        std::vector<Texture> textures;
        unsigned int textureCount = mat->GetTextureCount(type);

        for(unsigned int i = 0; i < textureCount; i++)
        {
            mat->GetTexture(type, i, &str);
            std::string texture_path = directory + '/' + std::string(str.C_Str());
            Texture texture(texture_path.c_str(), texType, i);
            std::cout << "Texture (push single) // ID:" <<  texture.ID << " Type: " << texture.type << " Path: " << texture_path << "\n"; // Type is still correct
            textures.push_back(texture);
        }

        for (unsigned int i = 0; i < textures.size(); i++)
        {
            Texture txt = textures[i];
            std::cout << "Texture "<< i << " // ID:" <<  txt.ID << " Type:" << txt.type <<"\n"; // Type is still correct
        }
        return textures;
    }

    glm::mat4 Model::ConvertMatrixToGLM(const aiMatrix4x4& from)
    {
        glm::mat4 to;
        to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
        to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
        to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
        to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
        return to;
    }
}

#include "Model.hpp"

namespace Future
{
    Model::Model(const char* file)
    {
        tinygltf::TinyGLTF loader;
        std::string err;
        std::string warn;

        bool ret = loader.LoadASCIIFromFile(&gltfModel, &err, &warn, file);

        if (!warn.empty()) {
            // "Warn: " << warn
        }

        if (!err.empty()) {
            //"Err: " << err
        }

        if (!ret) {
            //<< "Failed to load glTF: " << file
            throw std::runtime_error("Failed to load glTF model.");
        }

        this->file = file;
        traverseNode(0); // Start traversing from the root node
    }

    void Model::Draw(Shaders& shader, Camera& camera)
    {
        for (unsigned int i = 0; i < meshes.size(); i++)
        {
            meshes[i].Draw(shader, camera, matricesMeshes[i]);
        }
    }

    void Model::loadMesh(unsigned int indMesh)
    {
        const tinygltf::Mesh &mesh = gltfModel.meshes[indMesh];

        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;

        for (const auto &primitive : mesh.primitives)
        {
            // Positions
            const tinygltf::Accessor &posAccessor = gltfModel.accessors[primitive.attributes.find("POSITION")->second];
            const tinygltf::BufferView &posView = gltfModel.bufferViews[posAccessor.bufferView];
            const float *positions = reinterpret_cast<const float*>(&(gltfModel.buffers[posView.buffer].data[posView.byteOffset + posAccessor.byteOffset]));

            // Normals
            const tinygltf::Accessor &normAccessor = gltfModel.accessors[primitive.attributes.find("NORMAL")->second];
            const tinygltf::BufferView &normView = gltfModel.bufferViews[normAccessor.bufferView];
            const float *normals = reinterpret_cast<const float*>(&(gltfModel.buffers[normView.buffer].data[normView.byteOffset + normAccessor.byteOffset]));

            // Texture coordinates
            const tinygltf::Accessor &texAccessor = gltfModel.accessors[primitive.attributes.find("TEXCOORD_0")->second];
            const tinygltf::BufferView &texView = gltfModel.bufferViews[texAccessor.bufferView];
            const float *texUVs = reinterpret_cast<const float*>(&(gltfModel.buffers[texView.buffer].data[texView.byteOffset + texAccessor.byteOffset]));

            for (size_t i = 0; i < posAccessor.count; ++i)
            {
                Vertex vertex;
                vertex.Position = glm::vec3(positions[i * 3 + 0], positions[i * 3 + 1], positions[i * 3 + 2]);
                vertex.Normal = glm::vec3(normals[i * 3 + 0], normals[i * 3 + 1], normals[i * 3 + 2]);
                vertex.TexCoords = glm::vec2(texUVs[i * 2 + 0], texUVs[i * 2 + 1]);
                vertex.color = glm::vec3(1.0f, 1.0f, 1.0f); // Default color
                vertices.push_back(vertex);
            }

            // Indices
            const tinygltf::Accessor &indexAccessor = gltfModel.accessors[primitive.indices];
            const tinygltf::BufferView &indexView = gltfModel.bufferViews[indexAccessor.bufferView];
            const unsigned short *bufIndices = reinterpret_cast<const unsigned short*>(&gltfModel.buffers[indexView.buffer].data[indexView.byteOffset + indexAccessor.byteOffset]);

            for (size_t i = 0; i < indexAccessor.count; ++i)
            {
                indices.push_back(bufIndices[i]);
            }

            // Combine vertices, indices, and textures into a Mesh
            std::vector<Texture> textures = getTextures(); // Get the associated textures
            meshes.push_back(Mesh(vertices, indices, textures));
        }
    }

    void Model::traverseNode(unsigned int nextNode, glm::mat4 matrix)
    {
        const tinygltf::Node &node = gltfModel.nodes[nextNode];

        glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::mat4 matNode = glm::mat4(1.0f);

        if (node.translation.size() == 3) {
            translation = glm::vec3(node.translation[0], node.translation[1], node.translation[2]);
        }

        if (node.rotation.size() == 4) {
            rotation = glm::quat(node.rotation[3], node.rotation[0], node.rotation[1], node.rotation[2]);
        }

        if (node.scale.size() == 3) {
            scale = glm::vec3(node.scale[0], node.scale[1], node.scale[2]);
        }

        if (node.matrix.size() == 16) {
            matNode = glm::make_mat4(node.matrix.data());
        }

        glm::mat4 trans = glm::translate(glm::mat4(1.0f), translation);
        glm::mat4 rot = glm::mat4_cast(rotation);
        glm::mat4 sca = glm::scale(glm::mat4(1.0f), scale);
        glm::mat4 matNextNode = matrix * matNode * trans * rot * sca;

        if (node.mesh >= 0) {
            translationsMeshes.push_back(translation);
            rotationsMeshes.push_back(rotation);
            scalesMeshes.push_back(scale);
            matricesMeshes.push_back(matNextNode);

            loadMesh(node.mesh);
        }

        for (size_t i = 0; i < node.children.size(); i++) {
            traverseNode(node.children[i], matNextNode);
        }
    }

    std::vector<Texture> Model::getTextures()
    {
        std::vector<Texture> textures;

        std::string fileStr = std::string(file);
        std::string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);

        for (unsigned int i = 0; i < gltfModel.images.size(); i++)
        {
            std::string texPath = gltfModel.images[i].uri;

            bool skip = false;
            for (unsigned int j = 0; j < loadedTexName.size(); j++)
            {
                if (loadedTexName[j] == texPath)
                {
                    textures.push_back(loadedTex[j]);
                    skip = true;
                    break;
                }
            }

            if (!skip)
            {
                if (texPath.find("baseColor") != std::string::npos)
                {
                    Texture diffuse = Texture((fileDirectory + texPath).c_str(), "diffuse", loadedTex.size());
                    textures.push_back(diffuse);
                    loadedTex.push_back(diffuse);
                    loadedTexName.push_back(texPath);
                }
                else if (texPath.find("metallicRoughness") != std::string::npos)
                {
                    Texture specular = Texture((fileDirectory + texPath).c_str(), "specular", loadedTex.size());
                    textures.push_back(specular);
                    loadedTex.push_back(specular);
                    loadedTexName.push_back(texPath);
                }
            }
        }
        return textures;
    }
}

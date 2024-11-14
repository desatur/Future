#include "Mesh.hpp"

namespace Future
{
    Mesh::Mesh(std::vector <Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        SetupMesh();
    }

    void Mesh::SetupMesh()
    {
        this->VAO.Bind();
        this->VBO.Bind();
        this->EBO.Bind();
        
        this->VBO.vertices = this->vertices;
        this->VBO.Update();

        this->EBO.indices = this->indices;
        this->EBO.Update();

        this->VAO.LinkAttrib(this->VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);                            // Vertex positions
        this->VAO.LinkAttrib(this->VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));          // Vertex normals
        this->VAO.LinkAttrib(this->VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));          // Vertex color
        this->VAO.LinkAttrib(this->VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));          // vertex texture coords

        this->VAO.Unbind();
        this->VBO.Unbind();
        this->EBO.Unbind();
    }

    void Mesh::Draw(Shaders &shader) 
    {
        shader.Activate();
        this->VAO.Bind();

        unsigned int numDiffuse = 0;
        unsigned int numSpecular = 0;
        for(unsigned int i = 0; i < textures.size(); i++)
        {
            std::string num;
            std::string type = textures[i].type;
            if (type == "diffuse")
            {
                num = std::to_string(numDiffuse++);
            }
            else if (type == "specular")
            {
                return; // Temporary
                num = std::to_string(numSpecular++);
            }
            //textures[i].texUnit(shader, (type + num).c_str(), i);
            textures[i].texUnit(shader, "diffuseTex", i); // Temporary
            textures[i].Bind();
        }

        glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
        this->VAO.Unbind();
    }  
} // Future
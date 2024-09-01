#include "Mesh.hpp"


namespace Future
{
    Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector<Texture>& textures)
    {
        Mesh::vertices = vertices;
        Mesh::indices = indices;
        Mesh::textures = textures;

        VAO.Bind(); // Bind VAO

        VBO VBO (vertices);
        EBO EBO (indices);

        VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0); // Position
        VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float))); // Color
        VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float))); // Texture Coordinate
        VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float))); // Normals

        VAO.Unbind();
        VBO.Unbind();
        EBO.Unbind();
    }

    void Mesh::Draw(Shaders &shaders, Camera &camera)
    {
        shaders.Activate();
        VAO.Bind();

        unsigned int numDiffuse = 0;
        unsigned int numSpecular = 0;

        for (unsigned int i = 0; i < textures.size(); i++)
        {
            std::string num;
            std::string type = textures[i].type;
            if (type == "diffuse")
            {
                num = std::to_string(numDiffuse++);
            }
            else if (type == "specular")
            {
                num = std::to_string(numSpecular++);
            }
            textures[i].texUnit(shaders, (type + num).c_str(), i);
            textures[i].Bind();
        }
        glUniform3f(glGetUniformLocation(shaders.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
        camera.Matrix(shaders, "camMatrix");

        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }

} // Future
#include "OpenGL.hpp"

#include <cmath>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shaders.hpp"
#include "Camera.hpp"
#include "Buffers/EBO.hpp"
#include "Buffers/VAO.hpp"
#include "Buffers/VBO.hpp"
#include "Textures/Texture.hpp"
#include "Mesh.hpp"

namespace Future
{
    OpenGL::OpenGL(Window* window)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    OpenGL::~OpenGL()
    {
        glfwTerminate();
    }

    bool OpenGL::Init()
    {
        Vertex vertices[] =
        { //               COORDINATES           /            COLORS          /           NORMALS         /       TEXTURE COORDINATES    //
            Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
            Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
            Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
            Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
        };

        // Indices for vertices order
        GLuint indices[] =
        {
            0, 1, 2,
            0, 2, 3
        };

        Vertex lightVertices[] =
        { //     COORDINATES     //
            Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
            Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
            Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
            Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
            Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
            Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
            Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
            Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
        };

        GLuint lightIndices[] =
        {
            0, 1, 2,
            0, 2, 3,
            0, 4, 7,
            0, 7, 3,
            3, 7, 6,
            3, 6, 2,
            2, 6, 5,
            2, 5, 1,
            1, 5, 4,
            1, 4, 0,
            4, 5, 6,
            4, 6, 7
        };

        GLFWwindow* glfwWindow = glfwCreateWindow(1920, 1080, "GLFW Window", NULL, NULL); // TODO: Migrate do SDL2 later
        glfwMakeContextCurrent(glfwWindow);

        gladLoadGL();
        glViewport(0, 0, 1920, 1080);

        Texture textures[]
        {
            Texture("planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
            Texture("planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
        };

        // Generates Shader object using shaders default.vert and default.frag
        Shaders shaderProgram("default.vert", "default.frag");
        // Store mesh data in vectors for the mesh
        std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
        std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
        std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
        // Create floor mesh
        Mesh floor(verts, ind, tex);


        // Shader for light cube
        Shaders lightShader("light.vert", "light.frag");
        // Store mesh data in vectors for the mesh
        std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
        std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
        // Create light mesh
        Mesh light(lightVerts, lightInd, tex);





        glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPos);

        glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::mat4 objectModel = glm::mat4(1.0f);
        objectModel = glm::translate(objectModel, objectPos);


        lightShader.Activate();
        glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
        glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        shaderProgram.Activate();
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
        glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

        // Enables the Depth Buffer
        glEnable(GL_DEPTH_TEST);

        // Creates camera object
        Camera camera(1920, 1080, glm::vec3(0.0f, 0.0f, 2.0f));

        while (true)
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Clear screen with color (black)
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers

            // Handles camera inputs
            camera.Inputs(glfwWindow);
            // Updates and exports the camera matrix to the Vertex Shader
            camera.UpdateMatrix(45.0f, 0.01f, 1000.0f);

            // Draws different meshes
            floor.Draw(shaderProgram, camera);
            light.Draw(lightShader, camera);


            // Swap the back buffer with the front buffer
            glfwSwapBuffers(glfwWindow);
            // Take care of all GLFW events
            glfwPollEvents();
        }

        shaderProgram.Delete();
        lightShader.Delete();

        glfwDestroyWindow(glfwWindow);
        return true;
    }
}

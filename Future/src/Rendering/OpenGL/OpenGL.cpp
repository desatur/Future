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
        // Vertices coordinates
        GLfloat vertices[] =
        { //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
            -1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
            -1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
             1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
             1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
        };

        // Indices for vertices order
        GLuint indices[] =
        {
            0, 1, 2,
            0, 2, 3
        };

        GLfloat lightVertices[] =
        { //     COORDINATES     //
            -0.1f, -0.1f,  0.1f,
            -0.1f, -0.1f, -0.1f,
             0.1f, -0.1f, -0.1f,
             0.1f, -0.1f,  0.1f,
            -0.1f,  0.1f,  0.1f,
            -0.1f,  0.1f, -0.1f,
             0.1f,  0.1f, -0.1f,
             0.1f,  0.1f,  0.1f
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

        Shaders shaderProgram("Shaders/default.vert", "Shaders/default.frag");

        VAO gl_VAO;
        gl_VAO.Bind();

        VBO gl_VBO (vertices, sizeof(vertices));
        EBO gl_EBO (indices, sizeof(indices));

        gl_VAO.LinkAttrib(gl_VBO, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0); // Position
        gl_VAO.LinkAttrib(gl_VBO, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float))); // Color
        gl_VAO.LinkAttrib(gl_VBO, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float))); // Texture Coordinate
        gl_VAO.LinkAttrib(gl_VBO, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float))); // Normals

        gl_VAO.Unbind();
        gl_VBO.Unbind();
        gl_EBO.Unbind();
        // ^ Unbind so we won't overwrite it

        // Shader for light cube
        Shaders lightShader("Shaders/light.vert", "Shaders/light.frag");
        // Generates Vertex Array Object and binds it
        VAO lightVAO;
        lightVAO.Bind();
        // Generates Vertex Buffer Object and links it to vertices
        VBO lightVBO(lightVertices, sizeof(lightVertices));
        // Generates Element Buffer Object and links it to indices
        EBO lightEBO(lightIndices, sizeof(lightIndices));
        // Links VBO attributes such as coordinates and colors to VAO
        lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
        // Unbind all to prevent accidentally modifying them
        lightVAO.Unbind();
        lightVBO.Unbind();
        lightEBO.Unbind();

        glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPos);

        glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::mat4 pyramidModel = glm::mat4(1.0f);
        pyramidModel = glm::translate(pyramidModel, pyramidPos);

        lightShader.Activate();
        glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
        glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        shaderProgram.Activate();
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
        glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

        Texture testTex("testTexture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
        Texture testTexSpecular("testTextureSpecular.png", GL_TEXTURE_2D, 1, GL_RGB, GL_UNSIGNED_BYTE);
        testTex.texUnit(shaderProgram, "tex0", 0);
        testTexSpecular.texUnit(shaderProgram, "tex1", 1);

        glEnable(GL_DEPTH_TEST); // Enable depth buffer

        Camera camera(1920, 1080, glm::vec3(0.0f, 0.0f, 3.0f));

        while (true)
        {
            // Specify the color of the background
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            // Clean the back buffer and depth buffer
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Handles camera inputs
            camera.Inputs(glfwWindow);
            // Updates and exports the camera matrix to the Vertex Shader
            camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

            // Tells OpenGL which Shader Program we want to use
            shaderProgram.Activate();
            // Exports the camera Position to the Fragment Shader for specular lighting
            glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
            // Export the camMatrix to the Vertex Shader of the pyramid
            camera.Matrix(shaderProgram, "camMatrix");
            // Binds texture so that is appears in rendering
            testTex.Bind();
            testTexSpecular.Bind();
            // Bind the VAO so OpenGL knows to use it
            gl_VAO.Bind();
            // Draw primitives, number of indices, datatype of indices, index of indices
            glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);


            // Tells OpenGL which Shader Program we want to use
            lightShader.Activate();
            // Export the camMatrix to the Vertex Shader of the light cube
            camera.Matrix(lightShader, "camMatrix");
            // Bind the VAO so OpenGL knows to use it
            lightVAO.Bind();
            // Draw primitives, number of indices, datatype of indices, index of indices
            glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
            // Swap the back buffer with the front buffer
            glfwSwapBuffers(glfwWindow);
            // Take care of all GLFW events
            glfwPollEvents();
        }

        gl_VAO.Delete();
        gl_VBO.Delete();
        gl_EBO.Delete();
        shaderProgram.Delete();

        glfwDestroyWindow(glfwWindow);
        return true;
    }
}

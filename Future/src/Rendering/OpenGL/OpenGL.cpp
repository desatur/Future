#include "OpenGL.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shaders.hpp"
#include "Camera.hpp"
#include "Model.hpp"

namespace Future
{
    OpenGL::OpenGL(Window* window)
    {
        m_window = window;
    }

    OpenGL::~OpenGL()
    {

    }

    bool OpenGL::Init()
    {
        gladLoadGL();
        glViewport(0, 0, 1920, 1080);

        // Generates Shader object using shaders default.vert and default.frag
        Shaders shaderProgram("Shaders/default.vert", "Shaders/default.frag");

        // Take care of all the light related things
        glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, lightPos);

        shaderProgram.Activate();
        glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

        // Enables the Depth Buffer
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // Creates camera object
        Camera camera(1920, 1080, glm::vec3(0.0f, 0.0f, 2.0f));

        Model test("ground/scene.gltf");

        while (m_window->IsRunning())
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Clear screen with color (black)
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers

            camera.UpdateMatrix(45.0f, 0.1f, 100.0f); // Updates and exports the camera matrix to the Vertex Shader

            test.Draw(shaderProgram, camera);

            m_window->Tick();
        }

        shaderProgram.Delete();
        return true;
    }
}
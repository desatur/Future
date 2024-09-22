#include "Renderer.hpp"
#define BACKEND "OPENGL"

namespace Future
{
    Renderer::Renderer(Window* window)
    {
        m_window = window;
        PreInitBackend();
    }

    Renderer::~Renderer()
    {
        m_shaderProgram->Delete();
    }

    void Renderer::PreInitBackend()
    {
        gladLoadGL();
    }

    void Renderer::InitBackend()
    {

    }

    void Renderer::Init()
    {
        glViewport(0, 0, 1920, 1080);
        Shaders m_shaderProgram("Shaders/default.vert", "Shaders/default.frag");
        m_shaderProgram.Activate();

        glEnable(GL_DEPTH_TEST); // Enable depth buffer
        glEnable(GL_BLEND); // Enable blending for transparency
        glEnable(GL_CULL_FACE); // Enable Face Culling
        glDepthFunc(GL_LESS); // Depth func/type
        glCullFace(GL_FRONT); // Cull front faces
        glFrontFace(GL_CCW);  // CCW is common
        glClearDepth(1.0); // Clear depth before drawing stuff

        Camera m_mainCamera(1920, 1080, glm::vec3(0.0f, 0.0f, 1.0f));

        Model test("bnuy/scene.gltf");

        while (m_window->IsRunning())
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Clear framebuffer
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear those buffers

            m_mainCamera.UpdateMatrix(45.0f, 0.1f, 100.0f); // Updates and exports the camera matrix to the Vertex Shader

            test.Draw(m_shaderProgram, m_mainCamera);

            SDL_Event e = m_window->Tick();
        }
    }
}
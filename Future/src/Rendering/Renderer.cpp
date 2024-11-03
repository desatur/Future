#include "Renderer.hpp"

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

        Model demo("D:/Sponza/glTF/sponza.gltf"); // Testing model

        auto frameDuration = std::chrono::milliseconds(1000 / 480);

        while (m_window->IsRunning())
        {
            auto frameStart = std::chrono::high_resolution_clock::now();

            glClearColor(0.0f, 0.0f, 0.1f, 1.0f); // Clear framebuffer
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear those buffers

            m_mainCamera.UpdateMatrix(90.0f, 0.1f, 1000.0f); // Updates and exports the camera matrix to the Vertex Shader

            demo.Draw(m_shaderProgram, m_mainCamera);

            SDL_Event e = m_window->Tick();
            m_mainCamera.DebugMove();
            
            auto frameEnd = std::chrono::high_resolution_clock::now(); // End timing
            auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
            if (frameTime < frameDuration) std::this_thread::sleep_for(frameDuration - frameTime);
        }
    }
}
#include "Renderer.hpp"

namespace Future
{
    Renderer::Renderer(Window* window)
    {
        m_window = window;
        PreInitBackend();
        InitBackend();
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
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // Makes sure messages are output immediately
        glDebugMessageCallback(glDebugOutput, nullptr);
    }

    void GLAPIENTRY Renderer::glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        // Ignore non-significant error/warning codes
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
            return;

        std::cerr << "OpenGL Debug message (" << id << "): " << message << std::endl;

        switch (source)
        {
            case GL_DEBUG_SOURCE_API:             std::cerr << "Source: API"; break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cerr << "Source: Window System"; break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cerr << "Source: Shader Compiler"; break;
            case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cerr << "Source: Third Party"; break;
            case GL_DEBUG_SOURCE_APPLICATION:     std::cerr << "Source: Application"; break;
            case GL_DEBUG_SOURCE_OTHER:           std::cerr << "Source: Other"; break;
        } std::cerr << std::endl;

        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR:               std::cerr << "Type: Error"; break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cerr << "Type: Deprecated Behaviour"; break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cerr << "Type: Undefined Behaviour"; break;
            case GL_DEBUG_TYPE_PORTABILITY:         std::cerr << "Type: Portability"; break;
            case GL_DEBUG_TYPE_PERFORMANCE:         std::cerr << "Type: Performance"; break;
            case GL_DEBUG_TYPE_MARKER:              std::cerr << "Type: Marker"; break;
            case GL_DEBUG_TYPE_PUSH_GROUP:          std::cerr << "Type: Push Group"; break;
            case GL_DEBUG_TYPE_POP_GROUP:           std::cerr << "Type: Pop Group"; break;
            case GL_DEBUG_TYPE_OTHER:               std::cerr << "Type: Other"; break;
        } std::cerr << std::endl;

        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:         std::cerr << "Severity: high"; break;
            case GL_DEBUG_SEVERITY_MEDIUM:       std::cerr << "Severity: medium"; break;
            case GL_DEBUG_SEVERITY_LOW:          std::cerr << "Severity: low"; break;
            case GL_DEBUG_SEVERITY_NOTIFICATION: std::cerr << "Severity: notification"; break;
        } std::cerr << std::endl;

        std::cerr << std::endl;
    }

    void Renderer::Init()
    {
        glViewport(0, 0, 1920, 1080);
        Shaders m_shaderProgram("Shaders/default.vert", "Shaders/default.frag");
        m_shaderProgram.Activate();

        glEnable(GL_DEPTH_TEST); // Enable depth buffer
        glEnable(GL_BLEND); // Enable blending for transparency
        //glEnable(GL_CULL_FACE); // Enable Face Culling
        glDepthFunc(GL_LESS); // Depth func/type
        //glCullFace(GL_FRONT); // Cull front faces
        glFrontFace(GL_CCW);  // CCW is common
        glClearDepth(1.0); // Clear depth before drawing stuff

        Camera m_mainCamera(1920, 1080, glm::vec3(0.0f, 0.0f, 0.0f));

        Model demo("D:/Sponza/glTF/sponza.gltf"); // Testing model

        while (m_window->IsRunning())
        {
            glClearColor(0.0f, 0.0f, 0.1f, 1.0f); // Clear framebuffer
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear those buffers

            m_mainCamera.UpdateMatrix(90.0f, 0.1f, 1000.0f); // Updates and exports the camera matrix to the Vertex Shader

            demo.Draw(m_shaderProgram, m_mainCamera);

            SDL_Event e = m_window->Tick();
            m_mainCamera.DebugMove();
            //Renderer::Assert();
        }
    }

    void Renderer::Assert()
    {
        GLenum errorCode;
        while ((errorCode = glGetError()) != GL_NO_ERROR)
        {
            std::string error;
            switch (errorCode)
            {
                case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
                case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
                case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
                //case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
                //case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
                case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
                case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            }
            std::cout << error << std::endl;
        }
    }
}
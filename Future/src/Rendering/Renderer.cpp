#include "Renderer.hpp"
#include "Instances.hpp"

namespace Future
{
    Renderer::Renderer(Window* window)
    {
        m_window = window;
        Future::Instances().renderer = this;
        PreInitBackend();
        InitBackend();
    }

    Renderer::~Renderer()
    {
        //m_defaultShaderProgram->Delete();
    }

    void Renderer::PreInitBackend()
    {
        width = 1920;
        height = 1080;
        gladLoadGL();
    }

    void Renderer::InitBackend()
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
    }

    void GLAPIENTRY Renderer::glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return; // Ignore non-significant error/warning codes
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
        ConstructPipeline();

        glm::vec4 lightColor = glm::vec4(10.0f, 10.0f, 10.0f, 1.0f);
        defaultShaderProgram->Activate();
        glUniform4f(glGetUniformLocation(defaultShaderProgram->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

        Camera m_mainCamera(width, height, glm::vec3(0.0f, 0.0f, 1.0f));
        Model helmet("D:/DamagedHelmet/glTF/DamagedHelmet.gltf");
        Model sponza("D:/Sponza/glTF/Sponza.gltf");

        RectangleVBO rectVBO;
        rectVBO.Bind();
        RectangleVAO rectVAO;
        rectVAO.Bind();
        rectVAO.LinkAttrib(rectVBO, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
        rectVAO.LinkAttrib(rectVBO, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    
        Future::FBO mainFramebuffer(width, height);
        Future::FBO postProcessingFramebuffer(width, height);
        postProcessingFramebuffer.ClearTex();
        Future::RBO mainRenderbuffer(width, height);
        mainFramebuffer.Bind();
        mainRenderbuffer.Bind();
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mainRenderbuffer.ID);

        auto fboStatusMain = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (fboStatusMain != GL_FRAMEBUFFER_COMPLETE) {
            std::cerr << "Main Framebuffer error: " << fboStatusMain << std::endl;
        }

        auto fboStatusPost = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (fboStatusPost != GL_FRAMEBUFFER_COMPLETE) {
            std::cerr << "Post-processing Framebuffer error: " << fboStatusPost << std::endl;
        }

        framebufferShaderProgram->Activate();
        glUniform1f(glGetUniformLocation(framebufferShaderProgram->ID, "gamma"), 2.2f);

        float radius = 1.0f;  // Radius of the circular path
        float speed = 2.5f;   // Speed of rotation

        while (m_window->IsRunning())
        {
            float time = SDL_GetTicks() / 1000.0f; // Time in seconds
            glm::vec3 lightPos = glm::vec3(
                radius * cos(speed * time),  // X coordinate
                0.5f,                        // Y coordinate (static height)
                radius * sin(speed * time)   // Z coordinate
            );

            defaultShaderProgram->Activate();
            mainFramebuffer.Bind();
            mainRenderbuffer.Bind();
            glClearColor(0.0f, 0.0f, 0.025f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);
            //glClearDepth(1.0);
            glUniform3f(glGetUniformLocation(defaultShaderProgram->ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

            m_mainCamera.DebugMove();
            m_mainCamera.UpdateMatrix(45.0f, 0.01f, 10000.0f);
            m_mainCamera.Matrix(*defaultShaderProgram, "camMatrix");

            //helmet.Draw(*defaultShaderProgram, m_mainCamera);
            sponza.Draw(*defaultShaderProgram, m_mainCamera);

            glBindFramebuffer(GL_FRAMEBUFFER, 0); // Bind the default framebuffer
            postProcessingFramebuffer.Bind();
            framebufferShaderProgram->Activate();

            postProcessingFramebuffer.Bind();
            glBindFramebuffer(GL_READ_FRAMEBUFFER, mainFramebuffer.ID);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, postProcessingFramebuffer.ID);
            glBlitFramebuffer(0, 0, 1920, 1080, 0, 0, 1920, 1080, GL_COLOR_BUFFER_BIT, GL_NEAREST);

            // Render to the default framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            framebufferShaderProgram->Activate();

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, postProcessingFramebuffer.TexID);
            
            rectVAO.Bind();
            glDisable(GL_DEPTH_TEST);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            m_window->Tick();
        }
    }

    void Renderer::ConstructPipeline()
    {
        glViewport(0, 0, width, height);

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glEnable(GL_FRAMEBUFFER_SRGB);
        glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_CULL_FACE);
        glDepthFunc(GL_LESS);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(1.0f, 1.0f);

        framebufferShaderProgram = new Shaders("Shaders/framebuffer.vert", "Shaders/framebuffer.frag");
        defaultShaderProgram = new Shaders("Shaders/default.vert", "Shaders/default.frag");
    }
}
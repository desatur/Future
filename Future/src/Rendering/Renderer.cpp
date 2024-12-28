#include "Renderer.hpp"

namespace Future
{
    Renderer* Renderer::instance = nullptr;
    Renderer::Renderer(Window* window){
        if (instance != nullptr) {
            throw std::runtime_error("Renderer instance already exists! Use Renderer::Get() to access it.");
        }
        instance = this;
        m_window = window;
        PreInitBackend();
        InitBackend();
    }

    Renderer::~Renderer(){
        //m_defaultShaderProgram->Delete();
    }

    Renderer Renderer::Get() {
        return *instance;
    }

    void Renderer::PreInitBackend()
    {
        width = 1920;
        height = 1080;
        gladLoadGL();
        /*
            GLAD Extensions:

            GL_ARB_debug_output (Not for release but whatever?)
            GL_ARB_texture_compression
            GL_ARB_texture_compression_bptc
            GL_ARB_texture_compression_rgtc
            GL_ARB_explicit_uniform_location
            GL_ARB_explicit_attrib_location
        */
        GLint contextFlags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &contextFlags);
        if (contextFlags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            FE_CORE_WARN("Debug context is enabled. Expect slow rendering!");
        }
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
        std::this_thread::sleep_for (std::chrono::milliseconds(16));
    }

    void Renderer::Init()
    {
        ConstructPipeline();

        ImGUIHandler imgui(m_window);

        glm::vec4 lightColor = glm::vec4(100.0f, 100.0f, 100.0f, 1.0f);
        defaultShaderProgram->Activate();
        glUniform4f(glGetUniformLocation(defaultShaderProgram->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

        Camera m_mainCamera(width, height, glm::vec3(0.0f, 0.0f, 1.0f));
        Model helmet("D:/DamagedHelmet/glTF/DamagedHelmet.gltf");
        //Model sponza("D:/SponzaIntel/ported.gltf");

        RectangleVBO rectVBO;
        rectVBO.Bind();
        RectangleVAO rectVAO;
        rectVAO.Bind();
        rectVAO.LinkAttrib(rectVBO, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*)0);
        rectVAO.LinkAttrib(rectVBO, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    
        Future::FBO mainFramebuffer(width, height);
        Future::FBO postProcessingFramebuffer(width, height);
        //postProcessingFramebuffer.ClearTex();
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
            imgui.NewFrame();
            glEnable(GL_DEPTH_TEST);
            glUniform3f(glGetUniformLocation(defaultShaderProgram->ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

            // 3D rendering
            m_mainCamera.DebugMove();
            m_mainCamera.UpdateMatrix(45.0f, 0.01f, 10000.0f);
            m_mainCamera.Matrix(*defaultShaderProgram, "camMatrix");

            helmet.Draw(*defaultShaderProgram, m_mainCamera);
            //sponza.Draw(*defaultShaderProgram, m_mainCamera);

            glBindFramebuffer(GL_FRAMEBUFFER, 0); // Bind the default framebuffer

            bool show_demo_window = true;
            ImGui::ShowDemoWindow(&show_demo_window);

            postProcessingFramebuffer.Bind();
            framebufferShaderProgram->Activate();
            postProcessingFramebuffer.Bind();
            glBindFramebuffer(GL_READ_FRAMEBUFFER, mainFramebuffer.ID);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, postProcessingFramebuffer.ID);
            glBlitFramebuffer(0, 0, 1920, 1080, 0, 0, 1920, 1080, GL_COLOR_BUFFER_BIT, GL_NEAREST);

            // Render to the default framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            framebufferShaderProgram->Activate();
            rectVAO.Bind();
            postProcessingFramebuffer.BindTex();
            glDisable(GL_DEPTH_TEST);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            imgui.DrawFrame();

            // Swap buffers and tick the window
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
        glEnable(GL_MULTISAMPLE);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_CULL_FACE);
        glDepthFunc(GL_LESS);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        //glEnable(GL_POLYGON_OFFSET_FILL);
        //glPolygonOffset(1.0f, 1.0f);

        framebufferShaderProgram = new Shaders("Shaders/framebuffer.vert", "Shaders/framebuffer.frag");
        defaultShaderProgram = new Shaders("Shaders/default.vert", "Shaders/default.frag", "Shaders/default.geom");
    }
}
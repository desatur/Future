#pragma once
#include "../Core.hpp"
#include "../Window/Window.hpp"
#include <../../../thirdParty/stb/stb_image.h>
#include <../../../thirdParty/glm/glm/gtc/matrix_transform.hpp>
#include <../../../thirdParty/glm/glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <../glm/glm.hpp>
#include <../../../thirdParty/glm/glm/gtc/matrix_transform.hpp>
#include <../../../thirdParty/glm/glm/gtc/type_ptr.hpp>
#include "Shaders/Shaders.hpp"
#include "Mesh/Model.hpp"
#include "Camera.hpp"
#include "Shaders/Shaders.hpp"
#include "Buffers/EBO.hpp"
#include "Buffers/VAO.hpp"
#include "Buffers/VBO.hpp"
#include "DrawLayers/Buffers/FBO.hpp"
#include "DrawLayers/Buffers/RBO.hpp"
#include "DrawLayers/Buffers/RectangleVBO.hpp"
#include "DrawLayers/Buffers/RectangleVAO.hpp"

namespace Future
{
    class FE_API Renderer
    {
        public:
            Renderer(Window* window);
            ~Renderer();

            void Init();
            [[nodiscard]] Camera* GetMainCamera() const { return m_mainCamera; }
            Shaders* defaultShaderProgram;
            Shaders* framebufferShaderProgram;
        private:
            void PreInitBackend();
            void InitBackend();
            void ConstructPipeline();
            static void GLAPIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
            GLsizei width;
            GLsizei height;
            Window* m_window;
            Camera* m_mainCamera;
            FBO* mainFramebuffer;
            FBO* postProcessingFramebuffer;
    };
}
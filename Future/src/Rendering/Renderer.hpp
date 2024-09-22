#ifndef OPENGL_HPP
#define OPENGL_HPP

#include "../Core.hpp"
#include "../Window/Window.hpp"
#include <../../../thirdParty/stb/stb_image.h>
#include <../../../thirdParty/glm/glm/glm.hpp>
#include <../../../thirdParty/glm/glm/gtc/matrix_transform.hpp>
#include <../../../thirdParty/glm/glm/gtc/type_ptr.hpp>
#include <../../../thirdParty/glad/include/glad/glad.h>
#include <../../../thirdParty/glfw/include/GLFW/glfw3.h>
#include <../../../thirdParty/glm/glm/glm.hpp>
#include <../../../thirdParty/glm/glm/gtc/matrix_transform.hpp>
#include <../../../thirdParty/glm/glm/gtc/type_ptr.hpp>
#include "Shaders.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "Shaders.hpp"
#include "Buffers/EBO.hpp"
#include "Buffers/VAO.hpp"
#include "Buffers/VBO.hpp"

namespace Future
{
    enum class Backend : std::uint8_t;

    class FE_API Renderer
    {
        public:
            Renderer(Window* window);
            ~Renderer();

            void Init();
        private:
            static void PreInitBackend();
            static void InitBackend();
            Window* m_window;
            Camera* m_mainCamera{};
            Shaders* m_shaderProgram{};
    };
}

#endif //OPENGL_HPP

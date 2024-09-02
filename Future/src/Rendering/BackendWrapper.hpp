#ifndef OPENGL_HPP
#define OPENGL_HPP

#include "../Core.hpp"
#include "../Window/Window.hpp"
#include <../../../thirdParty/glad/include/glad/glad.h>
#include <../../../thirdParty/glfw/include/GLFW/glfw3.h>
#include <../../../thirdParty/stb/stb_image.h>
#include <../../../thirdParty/glm/glm/glm.hpp>
#include <../../../thirdParty/glm/glm/gtc/matrix_transform.hpp>
#include <../../../thirdParty/glm/glm/gtc/type_ptr.hpp>
#include "Shaders.hpp"
#include "Buffers/EBO.hpp"
#include "Buffers/VAO.hpp"
#include "Buffers/VBO.hpp"

namespace Future
{
    enum class Backend : std::uint8_t;

    class FE_API BackendWrapper
    {
        public:
            BackendWrapper(Window* window, Backend backend);
            ~BackendWrapper();

            bool Init();

        private:
            Window* m_window;
            Backend m_backend;
    };
}

#endif //OPENGL_HPP

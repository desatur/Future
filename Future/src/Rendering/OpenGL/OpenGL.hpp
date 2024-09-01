#ifndef OPENGL_HPP
#define OPENGL_HPP

#include "../../Core.hpp"
#include "../../Window/Window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shaders.hpp"
#include "Buffers/EBO.hpp"
#include "Buffers/VAO.hpp"
#include "Buffers/VBO.hpp"

namespace Future
{
    class FE_API OpenGL
    {
        public:
            OpenGL(Window* window);
            ~OpenGL();

            bool Init(); // Initialization method

        private:
            Window* m_window;
    };
}

#endif //OPENGL_HPP

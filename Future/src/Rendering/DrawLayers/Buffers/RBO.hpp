#pragma once
#include <vector>
#include <glad/glad.h>

namespace Future {
    class RBO {
        public:
            GLuint ID;
            RBO(GLuint width, GLuint height);

            void Bind();
            void Unbind();
            //void Delete();
    };
}
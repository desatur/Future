#pragma once
#include <vector>
#include <glad/glad.h>
//#include "../../Renderer.hpp"

namespace Future {
    class FBO {
        public:
            GLuint ID;
            GLuint TexID;
            FBO(GLuint width, GLuint height, bool multisample = false);

            void Bind();
            void Unbind();
            void BindTex();
            void UnbindTex();
            //void ClearTex();
    };
}
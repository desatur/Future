#ifndef FBO_HPP
#define FBO_HPP
#include <vector>
#include <glad/glad.h>

namespace Future
{
    class FBO
    {
        public:
            GLuint ID;
            GLuint TexID;
            FBO(GLuint width, GLuint height, bool multisample = false);

            void Bind();
            void Unbind();
            void BindTex();
            void UnbindTex();
            void ClearTex();
    };
}

#endif FBO_HPP
#ifndef RBO_HPP
#define RBO_HPP
#include <vector>
#include <glad/glad.h>

namespace Future
{
    class RBO
    {
        public:
            GLuint ID;
            RBO(GLuint width, GLuint height);

            void Bind();
            void Unbind();
            //void Delete();
    };
}

#endif RBO_HPP
#pragma once
#include <vector>
#include <glad/glad.h>

namespace Future {
    class EBO {
        public:
            GLuint ID;
            EBO();
            EBO(std::vector<GLuint>& indices);
            std::vector<GLuint> indices;

            void Update();
            void Bind();
            void Unbind();
            void Delete();
    };
}

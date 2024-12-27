#pragma once
#include <glad/glad.h>
#include "vec2.hpp"
#include "vec3.hpp"
#include "../Vertex.hpp"

namespace Future {
    class VBO {
        public:
            GLuint ID;
            VBO();
            VBO(std::vector<Vertex>& vertices);
            std::vector<Vertex> vertices;

            void Update();
            void Bind();
            void Unbind();
            void Delete();
    };
};

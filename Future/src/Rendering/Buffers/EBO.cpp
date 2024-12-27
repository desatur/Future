#include "EBO.hpp"

namespace Future {
    EBO::EBO() {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }
    
    EBO::EBO(std::vector<GLuint>& indices) {
        this->indices = indices;
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        Update();
    }

    void EBO::Update() {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), this->indices.data(), GL_STATIC_DRAW);
    }

    void EBO::Bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    }

    void EBO::Unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void EBO::Delete() {
        glDeleteBuffers(1, &ID);
    }
}
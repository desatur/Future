#include "VBO.hpp"

namespace Future {
    VBO::VBO() {
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    VBO::VBO(std::vector<Vertex>& vertices) {
        this->vertices = vertices;
        glGenBuffers(1, &ID);
        glBindBuffer(GL_ARRAY_BUFFER, ID);
        Update();
    }

    void VBO::Update() {
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), this->vertices.data(), GL_STATIC_DRAW);
    }

    void VBO::Bind() {
        glBindBuffer(GL_ARRAY_BUFFER, ID);
    }

    void VBO::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VBO::Delete()
    {
        glDeleteBuffers(1, &ID);
    }
}

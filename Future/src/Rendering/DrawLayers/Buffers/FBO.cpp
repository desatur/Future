#include "FBO.hpp"

namespace Future {
    FBO::FBO(GLuint width, GLuint height, bool multisample) {
        glGenFramebuffers(1, &ID);
        Bind();
        glGenTextures(1, &TexID);
        BindTex();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TexID, 0);
    }

    void FBO::Bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, ID);
    }

    void FBO::Unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void FBO::BindTex() {
        glBindTexture(GL_TEXTURE_2D, TexID);
    }

    void FBO::UnbindTex() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    /*
    void FBO::ClearTex() {
        GLint prevShaderId;
        glGetIntegerv(GL_CURRENT_PROGRAM, &prevShaderId);
        auto renderer = Future::Renderer::Get();
        renderer.framebufferShaderProgram->Activate();
        glUniform1i(glGetUniformLocation(renderer.framebufferShaderProgram->ID, "screenTexture"), 0);
        glUseProgram(prevShaderId);
    }
    */
}
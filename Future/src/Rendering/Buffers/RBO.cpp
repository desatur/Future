#include "RBO.hpp"

namespace Future
{
    RBO::RBO(GLuint width, GLuint height)
    {
        glGenRenderbuffers(1, &ID);
        Bind();
        //glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8 /*samples here*/, GL_DEPTH24_STENCIL8, width, height);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, ID);
    }

    void RBO::Bind()
    {
        glBindRenderbuffer(GL_RENDERBUFFER, ID);
    }

    void RBO::Unbind()
    {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }
}
#include "../Headers/Framebuffer.h"
#include "../Headers/Renderer.h"

Framebuffer::Framebuffer() {
	GLCall(glGenFramebuffers(1, &m_fb));
}

Framebuffer::~Framebuffer() {
	GLCall(glDeleteFramebuffers(1, &m_fb));
}

void Framebuffer::Bind() {
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fb));
}

void Framebuffer::Unbind() {
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void Framebuffer::CheckStatus() const {
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

void Framebuffer::AttachTexture(unsigned int texture) {
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D, texture, 0));
}

void Framebuffer::AttachRenderbuffer(unsigned int rb, GLenum type) {
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, type, GL_RENDERBUFFER, rb));
}

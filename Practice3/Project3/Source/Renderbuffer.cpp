#include "../Headers/Renderbuffer.h"
#include "../Headers/Renderer.h"

Renderbuffer::Renderbuffer(GLenum type, unsigned int width, unsigned int height) {
	GLCall(glGenRenderbuffers(1, &m_rb));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_rb));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, type, width, height));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

Renderbuffer::~Renderbuffer() {
	GLCall(glDeleteRenderbuffers(1, &m_rb));
}

void Renderbuffer::Bind() {
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_rb));
}

void Renderbuffer::Unbind() {
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

unsigned int Renderbuffer::GetID() const{
	return m_rb;
}

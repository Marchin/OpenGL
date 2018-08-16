#include "../Headers/UniformBuffer.h"
#include "../Headers/Renderer.h"

UniformBuffer::UniformBuffer(unsigned int size) {
	GLCall(glGenBuffers(1, &m_ub));
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_ub));
	GLCall(glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}

UniformBuffer::~UniformBuffer() {
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}

void UniformBuffer::SetSubData(void* pData, unsigned int size, unsigned int offsetSize) {
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_ub));
	GLCall(glBufferSubData(GL_UNIFORM_BUFFER, offsetSize, size, pData));
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}

void UniformBuffer::Bind() const {
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_ub));
}

void UniformBuffer::Unbind() const {
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
}

unsigned int UniformBuffer::GetID() const {
	return m_ub;
}

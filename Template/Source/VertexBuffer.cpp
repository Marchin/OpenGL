#include "../Headers/VertexBuffer.h"
#include "../Headers/Renderer.h"
#include <GLAD/glad.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	GLCall(glGenBuffers(1, &m_vertexBufferObject));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() {
	GLCall(glDeleteBuffers(1, &m_vertexBufferObject));
}

void VertexBuffer::Bind() const {
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject));
}

void VertexBuffer::Unbind() const{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

unsigned int VertexBuffer::GetID() const {
	return m_vertexBufferObject;
}

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

class VertexBuffer {
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
	unsigned int GetID() const;

private:
	unsigned int m_vertexBufferObject;
};


#endif //VERTEXBUFFER_H
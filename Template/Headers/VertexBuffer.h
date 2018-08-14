#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

class VertexBuffer {
public:
	VertexBuffer();
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void Bind() const;
	void Unbind() const;
	unsigned int GetID() const;
	void SetData(const void * data, unsigned int size);
private:
	unsigned int m_vb;
};


#endif //VERTEXBUFFER_H
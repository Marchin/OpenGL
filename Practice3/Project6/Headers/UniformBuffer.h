#ifndef UNIFORM_BUFFER_H
#define UNIFORM_BUFFER_H

class UniformBuffer {
public:
	UniformBuffer(unsigned int size);
	~UniformBuffer();
	void SetSubData(void* pData, unsigned int size, unsigned int offsetSize);
	void Bind() const;
	void Unbind() const;
	unsigned int GetID() const;
private:
	unsigned int m_ub;
};

#endif // !UNIFORM_BUFFER_H


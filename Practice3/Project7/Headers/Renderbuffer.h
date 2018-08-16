#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H
#include <GLAD/glad.h>

class Renderbuffer {
public:
	Renderbuffer(GLenum type, unsigned int width, unsigned int height);
	~Renderbuffer();
	void Bind() const;
	void Unbind() const;
	unsigned int GetID() const;
private:
	unsigned int m_rb;
};

#endif // !RENDERBUFFER_H

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <GLAD/glad.h>
#include "Texture.h"

class Framebuffer {
public:
	Framebuffer();
	~Framebuffer();
	void Bind();
	void Unbind();
	void CheckStatus() const;
	void AttachTexture(unsigned int texture);
	void AttachRenderbuffer(unsigned int rb, GLenum type);
private:
	unsigned int m_fb;
};

#endif // !FRAMEBUFFER_H

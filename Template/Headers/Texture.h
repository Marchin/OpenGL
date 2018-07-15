#ifndef TEXTURE_H
#define TEXTURE_H

#include <GLAD/glad.h>

class Texture {
public:
	Texture(const char* imgPath, const GLint  TextureWrap_S, const GLint  TextureWrap_T,
		const GLint  TextureMinFilter, const GLint  TextureMagFilter, const bool flipVertical = false);
	~Texture();
	void Bind(unsigned int slot) const;
	unsigned int GetID() const;
private:
	inline GLenum AnalizeFormat(const char* imgPath);
	unsigned int m_texture;
};

#endif //TEXTURE_H
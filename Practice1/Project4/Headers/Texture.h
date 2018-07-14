#ifndef TEXTURE_H
#define TEXTURE_H

#include <GLAD/glad.h>

class Texture {
public:
	Texture(const char* imgPath, GLuint TextureWrap_S, GLuint TextureWrap_T,
		GLuint TextureMinFilter, GLuint TextureMagFilter, const bool flipVertical = false);
	~Texture();
	unsigned int GetID() const;
private:
	inline GLuint AnalizeFormat(const char* imgPath);
	unsigned int m_texture;
};

#endif //TEXTURE_H
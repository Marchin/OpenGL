#include "../Headers/Texture.h"
#include "../Headers/stb_image.h"
#include "../Headers/Renderer.h"
#include <iostream>
#define PNG "gnp"

Texture::Texture(const char* imgPath, const GLint  TextureWrap_S, const GLint  TextureWrap_T,
	const GLint  TextureMinFilter, const GLint  TextureMagFilter, const bool flipVertical) {

	GLCall(glGenTextures(1, &m_texture));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_texture));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrap_S));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrap_T));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureMinFilter));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureMagFilter));
	stbi_set_flip_vertically_on_load(flipVertical);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(imgPath, &width, &height, &nrChannels, 0);
	if (data) {
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
			0, AnalizeFormat(imgPath), GL_UNSIGNED_BYTE, data));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

Texture::~Texture() {
	GLCall(glDeleteTextures(1, &m_texture));
}

void Texture::Bind(unsigned int slot) const {
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_texture));
}

unsigned int Texture::GetID() const {
	return m_texture;
}

inline GLenum Texture::AnalizeFormat(const char* imgPath) {
	char format[8] = { 0 };
	int j = strlen(imgPath) - 1;
	int i = 0;

	while (imgPath[j] != '.') {
		format[i++] = imgPath[j--];
	}
	if (!strcmp(format, PNG)) {
		return GL_RGBA;
	} else {
		return GL_RGB;
	}
}

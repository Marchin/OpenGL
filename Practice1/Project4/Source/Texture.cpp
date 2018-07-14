#include "../Headers/Texture.h"
#include "../Headers/stb_image.h"
#include "../Headers/Renderer.h"
#include <iostream>

Texture::Texture(const char* imgPath, GLuint TextureWrap_S, GLuint TextureWrap_T,
	GLuint TextureMinFilter, GLuint TextureMagFilter, const bool flipVertical) {

	GLCall(glGenTextures(1, &m_texture));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_texture));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	stbi_set_flip_vertically_on_load(flipVertical);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(imgPath, &width, &height, &nrChannels, 0);
	if (data) {
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,width, height,
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

unsigned int Texture::GetID() const {
	return m_texture;
}

inline GLuint Texture::AnalizeFormat(const char* imgPath) {
	char format[8] = { 0 };
	int j = strlen(imgPath) - 1;
	int i = 0;

	while (imgPath[j] != '.') {
		format[i++] = imgPath[j--];
	}
	if (!strcmp(format, "gnp")) {
		return GL_RGBA;
	} else {
		return GL_RGB;
	}
}

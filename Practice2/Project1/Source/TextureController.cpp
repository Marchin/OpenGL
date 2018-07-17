#include "../Headers/TextureController.h"
#include "../Headers/Renderer.h"
#include <iostream>

TextureController::TextureController() 
	: m_count(0){
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_maxTextures);
}

TextureController::~TextureController() {
}

void TextureController::AddTexture(const Texture& texture) {
	if ((int)m_count < m_maxTextures) {
		texture.Bind(m_count++);
	} else {
		std::cout << "No more texture slots available" << std::endl;
	}
}

void TextureController::Reset() {
	m_count = 0;
}

#include "../Headers/TextureController.h"
#include "../Headers/Renderer.h"
#include <iostream>

TextureController::TextureController() 
	: m_count(0){
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_maxTextures);
}

TextureController::~TextureController() {
}

void TextureController::AddTexture(Texture texture) {
	if (m_count < m_maxTextures) {
		GLCall(glActiveTexture(GL_TEXTURE0 + m_count++));
		GLCall(glBindTexture(GL_TEXTURE_2D, texture.GetID()));
	} else {
		std::cout << "No more texture slots available" << std::endl;
	}
}

void TextureController::Reset() {
	m_count = 0;
}

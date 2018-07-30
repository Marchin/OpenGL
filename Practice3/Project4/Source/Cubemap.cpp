#include "../Headers/Cubemap.h"
#include "../Headers/stb_image.h"
#include "../Headers/Renderer.h"

Cubemap::Cubemap(std::vector<std::string> fileNames) {
	int width, height, nrChannels;
	unsigned char *data;
	GLCall(glGenTextures(1, &m_cubemap));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemap));
	for (unsigned int i = 0; i < fileNames.size(); i++) {
		data = stbi_load(fileNames[i].c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			GLCall(glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			));
			stbi_image_free(data);
		}
		else {
			std::cout << "Cubemap texture failed to load at path: " << fileNames[i] << std::endl;
			stbi_image_free(data);
		}
	}
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
}

Cubemap::~Cubemap() {
}

void Cubemap::Bind() const {
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemap));
}

void Cubemap::Unbind() const {
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

unsigned int Cubemap::GetID() const {
	return m_cubemap;
}

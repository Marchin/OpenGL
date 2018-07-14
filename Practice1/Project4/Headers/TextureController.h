#ifndef TEXTURECONTOLLER_H
#define TEXTURECONTOLLER_H

#include "Texture.h"
#include <vector>

class TextureController {
public:
	TextureController();
	~TextureController();
	void AddTexture(Texture texture);
	void Reset();

private:
	int m_count;
	int m_maxTextures;
};
#endif // !TEXTURECONTOLLER_H


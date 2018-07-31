#ifndef TEXTURECONTOLLER_H
#define TEXTURECONTOLLER_H

#include "Texture.h"
#include "Cubemap.h"

namespace marchinGL {
	class TextureController {
	public:
		TextureController();
		~TextureController();
		void AddTexture(const Texture& texture);
		void AddTexture(const Cubemap& texture);
		void Reset();

	private:
		unsigned int m_count;
		int m_maxTextures;
	};
}
#endif // !TEXTURECONTOLLER_H


#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <vector>
#include "ITexture.h"

class Cubemap : public ITexture {
public:
	Cubemap(std::vector<std::string> fileNames);
	~Cubemap();
	void Bind(unsigned int slot) const override;
	void Unbind() const;
	unsigned int GetID() const override;
private:
	unsigned int m_cubemap;
};

#endif // !CUBEMAP_H


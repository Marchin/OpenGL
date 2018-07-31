#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <vector>

class Cubemap : public ITexture {
public:
	Cubemap(std::vector<std::string> fileNames);
	~Cubemap();
	void Bind(unsigned int slot) const;
	void Unbind() const;
	unsigned int GetID() const;
private:
	unsigned int m_cubemap;
};

#endif // !CUBEMAP_H


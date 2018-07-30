#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <vector>

class Cubemap {
public:
	Cubemap(std::vector<std::string> fileNames);
	~Cubemap();
	void Bind() const;
	void Unbind() const;
	unsigned int GetID() const;
private:
	unsigned int m_cubemap;
};

#endif // !CUBEMAP_H


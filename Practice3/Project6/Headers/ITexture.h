#ifndef ITEXTURE_H
#define ITEXTURE_H

class ITexture {
public:
	virtual void Bind(unsigned int slot) const = 0;
	virtual unsigned int GetID() const = 0;
	virtual ~ITexture() {}
};


#endif // !ITEXTURE_H


#ifndef UNIFORM_CONTROLLER_H
#define UNIFORM_CONTROLLER_H

#include <unordered_map>

class Shader;
class UniformBuffer;

class UniformController {
public:
	UniformController();
	~UniformController();
	void BindBlock(Shader shader, const char* name);
	void CreateUniformBuffer(const char* name, unsigned int size);
	void CreateUniformBuffer(const char* name, unsigned int size, unsigned int offsetSize);
	void SetUBSubData(const char* name, void* pData, unsigned int size, unsigned int offsetSize);
private:
	void SetupUniformBuffer(const char* name, unsigned int size);
	std::unordered_map<const char*, unsigned int> m_bindingPointCache;
	std::unordered_map<const char*, UniformBuffer*> m_pUBs;
	unsigned int m_cant;
};

#endif // !UNIFORM_CONTROLLER_H

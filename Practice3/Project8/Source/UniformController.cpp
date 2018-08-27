#include "../Headers/UniformController.h"
#include "../Headers/Renderer.h"
#include "../Headers/UniformBuffer.h"

UniformController::UniformController()
	: m_cant(0) {
}

UniformController::~UniformController() {
	std::unordered_map<const char*, UniformBuffer*>::iterator ipUB;
	for (ipUB = m_pUBs.begin(); ipUB != m_pUBs.end(); ipUB++) {
		if (ipUB->second != nullptr) {
			delete ipUB->second;
		}
	}
}

void UniformController::BindBlock(Shader shader, const char* name) {
	GLCall(unsigned int uiLocation = glGetUniformBlockIndex(shader.ID, name));
	if (m_bindingPointCache.find(name) == m_bindingPointCache.end()) {
		m_bindingPointCache[name] = m_cant;
		m_cant++;
	}
	GLCall(glUniformBlockBinding(shader.ID, uiLocation, m_bindingPointCache[name]));
}

void UniformController::CreateUniformBuffer(const char* name, unsigned int size) {
	if (m_pUBs.find(name) == m_pUBs.end()) {
		SetupUniformBuffer(name, size);
		GLCall(glBindBufferBase(GL_UNIFORM_BUFFER, m_bindingPointCache[name], m_pUBs[name]->GetID()));
	} else {
		std::cerr << "A uniform object with that name already exist" << std::endl;
	}
}

void UniformController::CreateUniformBuffer(const char* name, unsigned int size, unsigned int offsetSize) {
	if (m_pUBs.find(name) == m_pUBs.end()) {
		SetupUniformBuffer(name, size);
		GLCall(glBindBufferRange(GL_UNIFORM_BUFFER, m_bindingPointCache[name], 
			m_pUBs[name]->GetID(), offsetSize, size));
	} else {
		std::cerr << "A uniform object with that name already exist" << std::endl;
	}
}

void UniformController::SetUBSubData(const char* name, void* pData, unsigned int size, unsigned int offsetSize) {
	if (m_pUBs.find(name) != m_pUBs.end()) {
		m_pUBs[name]->SetSubData(pData, size, offsetSize);
	} else {
		std::cerr << "Uniform object not found" << std::endl;
	}
}

void UniformController::SetupUniformBuffer(const char* name, unsigned int size) {
	UniformBuffer* ub = new UniformBuffer(size);
	if (m_bindingPointCache.find(name) == m_bindingPointCache.end()) {
		m_bindingPointCache[name] = m_cant;
		m_cant++;
	}
	m_pUBs[name] = ub;
}

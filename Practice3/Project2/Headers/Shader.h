#ifndef SHADER_H
#define SHADER_H

#include <GLAD/glad.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	unsigned int ID;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void Bind() const;
	void SetBool(const std::string &name, bool vale);
	void SetInt(const std::string &name, int value);
	void SetFloat(const std::string &name, float value);
	void SetMat4(const std::string &name, const glm::mat4 &mat);
	int GetUniformLocation(const std::string &name);
private:
	void CheckCompileErrors(unsigned int shader, std::string type);
	std::unordered_map<std::string, int> m_uniformLocationCache;
};

#endif // !SHADER_H

#include "../Headers/Shader.h"
#include "../Headers/Renderer.h"

Shader::Shader(const GLchar * vertexPath, const GLchar * fragmentPath){
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}catch (std::ifstream::failure e){
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	GLCall(glShaderSource(vertex, 1, &vShaderCode, NULL));
	GLCall(glCompileShader(vertex));
	CheckCompileErrors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	GLCall(glShaderSource(fragment, 1, &fShaderCode, NULL));
	GLCall(glCompileShader(fragment));
	CheckCompileErrors(fragment, "FRAGMENT");

	ID = glCreateProgram();
	GLCall(glAttachShader(ID, vertex));
	GLCall(glAttachShader(ID, fragment));
	GLCall(glLinkProgram(ID));
	CheckCompileErrors(ID, "PROGRAM");

	GLCall(glDeleteShader(vertex));
	GLCall(glDeleteShader(fragment));
}

void Shader::Bind() const{
	GLCall(glUseProgram(ID));
}

void Shader::SetBool(const std::string & name, bool value) {
	GLCall(glUniform1i(GetUniformLocation(name.c_str()), (int)value));
}

void Shader::SetInt(const std::string & name, int value) {
	GLCall(glUniform1i(GetUniformLocation(name.c_str()), value));
}

void Shader::SetFloat(const std::string & name, float value) {
	GLCall(glUniform1f(GetUniformLocation(name.c_str()), value));
}

void Shader::SetMat4(const std::string & name, const glm::mat4 & mat) {
	GLCall(glUniformMatrix4fv(GetUniformLocation(name.c_str()), 1, GL_FALSE, &mat[0][0]));
}

int Shader::GetUniformLocation(const std::string & name) {
	if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
		return m_uniformLocationCache[name];
	} else {
		GLCall(int location = glGetUniformLocation(ID, name.c_str()));
		if (location == -1) {
			std::cout << "Warning: uniform '" << name << "' doesn't exist" << std::endl;
		}
		m_uniformLocationCache[name] = location;
		return location;
	}
}

void Shader::CheckCompileErrors(unsigned int shader, std::string type){
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" 
				<< infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		} else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" 
					<< infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
}

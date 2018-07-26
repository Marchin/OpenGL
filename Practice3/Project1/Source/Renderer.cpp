#include "../Headers/Renderer.h"
#include <iostream>

void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << "): " << function
			<< " " << file << ": " << line << std::endl;
		return false;
	}
	return true;
}


Renderer::Renderer() {
	GLCall(glEnable(GL_DEPTH_TEST));
}

Renderer::~Renderer() {
}

void Renderer::Draw(const VertexArray & va, const ElementBuffer & eb, 
	const Shader & shader) const{

	shader.Bind();
	va.Bind();
	eb.Bind();
	GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
}

void Renderer::Clear() const{
	GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT 
		| GL_STENCIL_BUFFER_BIT));
}

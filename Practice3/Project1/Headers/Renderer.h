#ifndef RENDERER_H
#define RENDERER_H

#include <GLAD/glad.h>
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shader.h"
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__));

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
	Renderer();
	~Renderer();
	void Draw(const VertexArray& va, const ElementBuffer& eb, 
		const Shader& shader) const;
	void Clear() const;
private:

};
#endif // !RENDERER_H


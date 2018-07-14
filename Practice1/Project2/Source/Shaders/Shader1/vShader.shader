#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aTexCoord;

uniform float offset;
uniform mat4 transform;

out vec4 verCol;
out vec2 TexCoord;

void main(){
	gl_Position = transform * vec4(aPos.x + offset, aPos.y, aPos.z, 1.0f);
	verCol = vec4(aCol, 1.0f);
	TexCoord = aTexCoord;
}
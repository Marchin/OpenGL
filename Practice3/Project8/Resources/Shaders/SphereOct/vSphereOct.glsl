#version 400 core

layout (location = 0) in vec3 aPos;

out vec3 vPos;

uniform mat4 uModel;
uniform mat4 uView;

void main(){
	vPos = uView * uModel * vec4(aPos, 1.0f);
	gl_Position = vec4(vPos, 1.0f);
}
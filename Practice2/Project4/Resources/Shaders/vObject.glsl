#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 vNormal;
out vec3 vVC;
out vec3 vVCLightPos;
out vec2 vTexCoord;

uniform vec3 lightPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    vNormal = mat3(transpose(inverse(view * model))) * aNormal;
    vVC = vec3(view * model * vec4(aPos,1.0));
    vVCLightPos = vec3(view * vec4(lightPos,1.0));
    vTexCoord = aTexCoord;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
#version 330 core
layout (location = 0) in vec3 aPos;

struct Matrices{
    mat4 projection;
    mat4 view;
};
uniform Matrices matrices;
uniform mat4 model;

void main(){
    gl_Position = matrices.projection * matrices.view 
        * model * vec4(aPos, 1.f);
}
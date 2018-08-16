#version 330 core

in vec3 gColor;

out vec4 fColor;

void main() {
    fColor = vec4(gColor, 1.f);
}
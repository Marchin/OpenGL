#version 330 core

in vec3 vTexDir;

out vec4 fColor;

uniform samplerCube cubemap;

void main() {
    fColor = texture(cubemap, vTexDir);
}
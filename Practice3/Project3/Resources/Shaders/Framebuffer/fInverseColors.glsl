#version 330 core

in vec3 vNormal;
in vec2 vTexCoords;

out vec4 fColor;

uniform sampler2D texture1;

void main() {    
  fColor = vec4(vec3(1.f - texture(texture1, vTexCoords)), 1.f);
}
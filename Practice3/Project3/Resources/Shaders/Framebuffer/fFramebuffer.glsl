#version 330 core

in vec3 vNormal;
in vec2 vTexCoords;

out vec4 fColor;

uniform sampler2D texture1;

void main() {    
  fColor = texture(texture1, vTexCoords);
}
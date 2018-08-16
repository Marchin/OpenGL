#version 330 core

in vec3 vNormal;
in vec2 gTexCoords;

out vec4 fColor;

uniform sampler2D texture_diffuse1;

void main() {    
  fColor = texture(texture_diffuse1, gTexCoords);
}
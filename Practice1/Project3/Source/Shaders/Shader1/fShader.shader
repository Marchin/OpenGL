#version 330 core

in vec4 verCol;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float graduation;

void main() {
	FragColor = mix(texture(texture1, TexCoord),
		texture(texture2, TexCoord), graduation);
}
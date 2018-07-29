#version 330 core

in vec3 vNormal;
in vec2 vTexCoords;

out vec4 fColor;

uniform sampler2D texture1;

void main() {    
    fColor = texture(texture1, vTexCoords);
    //float average = (fColor.r + fColor.g + fColor.b) / 3.f;
    float average = 0.2126 * fColor.r + 0.7152 * fColor.g + 0.0722 * fColor.b;
    fColor = vec4(vec3(average), 1.f);
}
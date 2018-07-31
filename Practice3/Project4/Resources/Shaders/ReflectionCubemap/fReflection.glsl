#version 330 core

in vec3 vNormal;
in vec3 vPosWC;

out vec4 fColor;

uniform vec3 cameraPos;
uniform samplerCube cubemap;

void main(){
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(vPosWC - cameraPos);
    vec3 reflection = reflect(I, normalize(vNormal));
    vec3 refraction = refract(I, normalize(vNormal), ratio);
    fColor = vec4(mix(texture(cubemap, reflection).rgb, texture(cubemap, refraction).rgb,
     .7f), 1.0);
}
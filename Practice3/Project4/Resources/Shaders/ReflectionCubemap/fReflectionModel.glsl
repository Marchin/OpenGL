#version 330 core

in vec3 vNormal;
in vec3 vPosWC;
in vec2 vTexCoords;

out vec4 fColor;

uniform vec3 cameraPos;
uniform samplerCube cubemap;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_reflection1;

void main(){
    float ratio = 1.00 / 1.52;
    vec3 I = normalize(vPosWC - cameraPos);
    vec3 reflection = reflect(I, normalize(vNormal));
    vec3 refraction = refract(I, normalize(vNormal), ratio);
    vec3 diffuse = texture(texture_diffuse1, vTexCoords).rgb;
    float reflectionFactor = texture(texture_reflection1, vTexCoords).x;
    vec3 reflectionMap = texture(cubemap, reflection).rgb;
    vec4 a = texture(texture_specular1, vTexCoords);
    vec4 v = texture(texture_normal1, vTexCoords);
    //fColor = vec4(mix(texture(cubemap, reflection).rgb, texture(cubemap, refraction).rgb, .7f), 1.0);
    //fColor = vec4(diffuse, 1.f);
    fColor = vec4(mix(diffuse, diffuse+reflectionMap, reflectionFactor), 1.0);
}
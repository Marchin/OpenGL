#version 330 core

in vec3 vNormal;
in vec3 vVC;
in vec3 vVCLightPos;
in vec2 vTexCoord;

out vec4 fColor;

uniform vec3 objectColor;

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};
uniform Material material;

struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

void main() {
	vec3 ambient = vec3(texture(material.diffuse, vTexCoord)) * light.ambient;

	vec3 nNormal = normalize(vNormal);
	vec3 nLightDir = normalize(vVCLightPos - vVC);
	float diff = max(dot(nNormal, nLightDir), 0.0f);
	vec3 diffuse = (vec3(texture(material.diffuse, vTexCoord))* diff) * light.diffuse;

	vec3 viewDir = normalize(-vVC);
	vec3 reflectDir = reflect(-nLightDir, nNormal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular= (vec3(texture(material.specular, vTexCoord)) * spec) * light.specular;
	
	vec3 emission = vec3(texture(material.emission, vTexCoord));

	vec3 result = (ambient + diffuse + specular + emission) * objectColor;
	fColor = vec4(result, 1.f);
}
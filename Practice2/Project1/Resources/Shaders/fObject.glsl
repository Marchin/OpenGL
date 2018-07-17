#version 330 core

in vec3 vNormal;
in vec3 vVC;
in vec3 vVCLightPos;

out vec4 fColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
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
	vec3 ambient = material.ambient * light.ambient;

	vec3 nNormal = normalize(vNormal);
	vec3 nLightDir = normalize(vVCLightPos - vVC);
	float diff = max(dot(nNormal, nLightDir), 0.0f);
	vec3 diffuse = (material.diffuse * diff) * light.diffuse;

	float specularStrength = 0.6f;
	vec3 viewDir = normalize(-vVC);
	vec3 reflectDir = reflect(-nLightDir, nNormal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular= (material.specular * spec) * light.specular;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	fColor = vec4(result, 1.f);
}
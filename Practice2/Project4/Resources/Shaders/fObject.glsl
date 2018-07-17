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
	float shininess;
};
uniform Material material;

struct Light{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float cuadratic;
};
uniform Light light;

void main() {
	float lightDist = length(vVCLightPos - vVC);
	float attenuation = 1.f/(light.constant + light.linear * lightDist 
		+ light.cuadratic * lightDist * lightDist);

	vec3 ambient = vec3(texture(material.diffuse, vTexCoord)) * light.ambient;

	vec3 nNormal = normalize(vNormal);
	vec3 nLightDir = normalize(vVCLightPos - vVC);
	float diff = max(dot(nNormal, nLightDir), 0.0f);
	vec3 diffuse = (vec3(texture(material.diffuse, vTexCoord))* diff) * light.diffuse;

	vec3 viewDir = normalize(-vVC);
	vec3 reflectDir = reflect(-nLightDir, nNormal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular= (vec3(texture(material.specular, vTexCoord)) * spec) * light.specular;

	ambient*=attenuation;
	diffuse*=attenuation;
	specular*=attenuation;
	vec3 result = (ambient + diffuse + specular) * objectColor;
	fColor = vec4(result, 1.f);
}
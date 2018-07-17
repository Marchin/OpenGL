#version 330 core

in vec3 vNormal;
in vec3 vVC;
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
	vec3 direction;
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};
uniform Light light;

void main() {
	vec3 nLightDir = normalize(light.position - vVC);
	float theta = dot(nLightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.f, 1.f);

	vec3 ambient = vec3(texture(material.diffuse, vTexCoord)) * light.ambient;

	vec3 nNormal = normalize(vNormal);
	float diff = max(dot(nNormal, nLightDir), 0.0f);
	vec3 diffuse = (vec3(texture(material.diffuse, vTexCoord))* diff) * light.diffuse;

	vec3 viewDir = normalize(light.position-vVC);
	vec3 reflectDir = reflect(-nLightDir, nNormal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
	vec3 specular= (vec3(texture(material.specular, vTexCoord)) * spec) * light.specular;

	float lightDist = length(light.position - vVC);
	float attenuation = 1.f/(light.constant + light.linear * lightDist 
		+ light.quadratic * lightDist * lightDist);
	//ambient*=attenuation;
	diffuse*=intensity;
	specular*=intensity;
	diffuse*=attenuation;
	specular*=attenuation;
	vec3 result = (ambient + diffuse + specular) * objectColor;
	fColor = vec4(result, 1.f);
}
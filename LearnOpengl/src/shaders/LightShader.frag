#version 330 core
uniform vec3 objectColor;

out vec4 FragColor;

void main()
{
	vec3 lightColor = vec3(1.0,1.0,1.0);
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	vec3 result = ambient * objectColor;
	FragColor = vec4(result, 1.0);
}
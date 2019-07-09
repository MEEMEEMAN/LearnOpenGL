#version 330 core
in vec3 Normal;

uniform vec3 ObjectColor;
uniform vec3 LightPos;

out vec4 FragColor;
in vec3 VertPos;

void main()
{
	vec3 lightColor = vec3(1.0, 1.0, 1.0);
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - VertPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	
	vec3 result = (ambient + diffuse) * ObjectColor;
	FragColor = vec4(result, 1.0);
}

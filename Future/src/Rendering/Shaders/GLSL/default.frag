#version 440 core

out vec4 FragColor; // Outputs colors in RGBA

in vec3 Normal;
in vec3 crntPos;
in vec3 color;
in vec2 texCoord;

struct Material {
    float ambientLightAmount;
	float specularLightAmount;
};

// Gets the Texture Units from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform sampler2D normal0;

// Material data
uniform Material material;

// Gets the light data
uniform vec4 lightColor;
uniform vec3 lightPos;

// Gets the position of the camera from the main function
uniform vec3 camPos;

void main()
{
	if (texture(diffuse0, texCoord).a < 0.1) { discard; } // Discard fully transparent pixels first
	Material material = Material(0.2, 0.5);

	vec3 lightVec = lightPos - camPos;
	vec3 lightDirection = normalize(lightVec);
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);
	
	vec3 normal = normalize(texture(normal0, texCoord).xyz * 2.0f - 1.0f);
	float diffuse = max(dot(normal, lightVec), 0.0f);
	
	float specular = 0.0f;
	if (diffuse != 0.0f) {
		vec3 reflection = reflect(-lightVec, normal);
		vec3 halfwayVec = normalize(camPos + lightVec);
		float specular = pow(max(dot(normal, halfwayVec), 0.0f), 16) * material.specularLightAmount;
	}

	FragColor = 
		(texture(diffuse0, texCoord) * (diffuse * inten + material.ambientLightAmount)) + 
		(texture(specular0, texCoord).r * (specular * inten * material.ambientLightAmount))
		* lightColor;
}
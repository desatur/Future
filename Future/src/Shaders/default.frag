#version 440 core

out vec4 FragColor; // Outputs colors in RGBA

// Imports the current position from the Vertex Shader
in vec3 crntPos;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;


// Gets the Texture Units from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform sampler2D normal0;

// Gets the light data
uniform vec4 lightColor;
uniform vec3 lightPos;

// Gets the position of the camera from the main function
uniform vec3 camPos;

void main()
{
	vec3 lightVec = lightPos - crntPos;

	float ambient = 0.20f;

	float dist = length(lightVec);
	float a = 1.00f;
	float b = 0.70f;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);
	
	vec3 normal = texture(normal0, texCoord).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	if (texture(diffuse0, texCoord).a < 0.1) { discard; }

	FragColor = texture(diffuse0, texCoord) * (diffuse * inten + ambient) * lightColor;
}
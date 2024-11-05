#version 440 core

out vec4 FragColor;

in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight()
{
    vec3 lightVec = lightPos - crntPos;
    float dist = length(lightVec);
    float a = 3.0;
    float b = 0.7;
    float inten = 1.0 / (a * dist * dist + b * dist + 1.0);

    float ambient = 0.2;
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightVec);
    float diffuse = max(dot(normal, lightDirection), 0.0);

    float specularLight = 0.5;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 16.0);
    float specular = specAmount * specularLight;

    return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

vec4 direcLight()
{
    float ambient = 0.2;
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(vec3(1.0, 1.0, 0.0));
    float diffuse = max(dot(normal, lightDirection), 0.0);

    float specularLight = 0.5;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 16.0);
    float specular = specAmount * specularLight;

    return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 spotLight()
{
    float outerCone = 0.9;
    float innerCone = 0.95;

    float ambient = 0.2;
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - crntPos);
    float diffuse = max(dot(normal, lightDirection), 0.0);

    float specularLight = 0.5;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 16.0);
    float specular = specAmount * specularLight;

    float angle = dot(vec3(0.0, -1.0, 0.0), -lightDirection);
    float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0, 1.0);

    return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

float near = 0.1;
float far = 100.0;

float linearizeDepth(float depth)
{
    return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

float logisticDepth(float depth, float steepness, float offset)
{
    float zVal = linearizeDepth(depth);
    return 1.0 / (1.0 + exp(-steepness * (zVal - offset)));
}

void main()
{
    float depth = logisticDepth(gl_FragCoord.z, 0.5, 5.0);
    FragColor = direcLight() * (1.0 - depth) + vec4(depth * vec3(0.85, 0.85, 0.9), 1.0);
}

#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;

uniform float gamma;

// EFFECTS
uniform bool sharpnessEnabled;  // Enable or disable the sharpening effect
uniform float sharpnessAmount; // Intensity of the sharpening kernel
uniform float sharpnessMix;    // Blending factor: 1.0 = no effect, <1.0 blends, >1.0 exaggerates

uniform bool grayscaleEnabled;   // Enable or disable grayscale
uniform float grayscaleMix;    // Blending factor: 1.0 = no effect, <1.0 blends, >1.0 exaggerates

void ApplySharpness(inout vec4 color, vec2 texCoords)
{
    vec2 texelSize = 1.0 / textureSize(screenTexture, 0); // Size of one texel
    vec4 center = texture(screenTexture, texCoords);
    vec4 north = texture(screenTexture, texCoords + vec2(0.0, texelSize.y));
    vec4 south = texture(screenTexture, texCoords - vec2(0.0, texelSize.y));
    vec4 east = texture(screenTexture, texCoords + vec2(texelSize.x, 0.0));
    vec4 west = texture(screenTexture, texCoords - vec2(texelSize.x, 0.0));
    vec4 sharpened = (1.0 + sharpnessAmount) * center - sharpnessAmount * (north + south + east + west);
    color = mix(center, sharpened, sharpnessMix);
}

void ApplyGrayscale(inout vec4 color, float grayscaleMix)
{
    float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114)); 
    vec3 grayscaleColor = vec3(gray);
    color.rgb = mix(color.rgb, grayscaleColor, grayscaleMix);
}

void main()
{
    vec4 screenTextureColor = texture(screenTexture, texCoords);
    float exposure = 0.1f;
    screenTextureColor.rgb = vec3(1.0f) - exp(-screenTextureColor.rgb * exposure);

    if (sharpnessEnabled) { ApplySharpness(screenTextureColor, texCoords); }
    //if (grayscaleEnabled) { ApplyGrayscale(screenTextureColor, grayscaleMix); }

    FragColor = vec4(pow(screenTextureColor.rgb, vec3(1.0f / gamma)), screenTextureColor.a);
}

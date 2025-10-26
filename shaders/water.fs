#version 330

// -----------------------------
// Inputs
in vec2 fragTexCoord;
in vec4 fragColor;

// -----------------------------
// Outputs
out vec4 finalColor;

// -----------------------------
// Uniforms
uniform sampler2D texture0;              // main texture
uniform sampler2D waterDepthGradient;
uniform sampler2D causticTexture;
uniform sampler2D causticHighlightTexture;
uniform sampler2D causticNoiseTexture;
uniform sampler2D causticFadeNoiseTexture;
uniform sampler2D specularNoiseTexture;
uniform sampler2D specularMovementLeftNoiseTexture;
uniform sampler2D specularMovementRightNoiseTexture;
uniform sampler2D foamTexture;

uniform float aspectRatio = 1.0;
uniform float pixelization = 2048.0;

uniform vec4 causticColor = vec4(0.455, 0.773, 0.765, 1.0);
uniform vec4 causticHighlightColor = vec4(0.741, 0.894, 0.898, 1.0);
uniform float causticScale = 12.0;
uniform float causticSpeed = 0.005;
uniform float causticMovementAmount = 0.15;
uniform float causticFaderMultiplier = 1.45;

uniform vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0);
uniform float specularThreshold = 0.35;
uniform float specularSpeed = 0.025;
uniform float specularScale = 15.0;

uniform vec4 foamColor = vec4(1.0, 1.0, 1.0, 1.0);
uniform float foamIntensity = 0.2;
uniform float foamScale = 15.0;

uniform vec4 outlineColor = vec4(0.675, 0.86, 1.0, 1.0);
uniform float generalTransparency = 1.0;

uniform float time;

// -----------------------------
// Helper functions

vec2 blendSubtract_vec2(vec2 base, vec2 blend, float opacity)
{
    vec2 result = base - blend;
    return mix(base, result, opacity);
}

float blendSubtract_float(float base, float blend, float opacity)
{
    float result = base - blend;
    return mix(base, result, opacity);
}

float blendOverlay_float(float base, float blend, float opacity)
{
    float result1 = 1.0 - 2.0 * (1.0 - base) * (1.0 - blend);
    float result2 = 2.0 * base * blend;
    float zeroOrOne = step(0.5, base);
    float res = result2 * zeroOrOne + (1.0 - zeroOrOne) * result1;
    return mix(base, res, opacity);
}

vec2 pixelizeCoordinates(vec2 coordinates)
{
    return floor(coordinates * pixelization) / pixelization;
}

vec2 applyAspectRatio(vec2 coordinates)
{
    return vec2(coordinates.x, coordinates.y * aspectRatio);
}

// -----------------------------
// Shader layers

vec4 caustics(vec2 pixelizedCoordinates)
{
    vec4 causticNoise = texture(causticNoiseTexture, time * causticSpeed + pixelizedCoordinates);
    vec2 noiseCoordinates = blendSubtract_vec2(pixelizedCoordinates * causticScale, causticNoise.rg, causticMovementAmount);
    vec4 causticHighlight = texture(causticHighlightTexture, noiseCoordinates) * causticHighlightColor;
    vec4 caustic = texture(causticTexture, noiseCoordinates) * causticColor;
    vec4 interpolatedCaustics = mix(caustic, causticHighlight, causticHighlight.a);
    float fadeNoise = texture(causticFadeNoiseTexture, noiseCoordinates).r * causticFaderMultiplier;
    return vec4(interpolatedCaustics.rgb, clamp(interpolatedCaustics.a - fadeNoise, 0.0, 1.0));
}

vec4 specular(vec2 pixelizedCoordinates)
{
    vec2 scaledCoordinates = pixelizedCoordinates * specularScale;
    float specularNoise = texture(specularNoiseTexture, scaledCoordinates).r;
    float leftScrollingNoise = texture(specularMovementLeftNoiseTexture, scaledCoordinates + vec2(time * specularSpeed, 0.0)).r;
    float rightScrollingNoise = texture(specularMovementRightNoiseTexture, scaledCoordinates + vec2(time * specularSpeed * -1.0, 0.0)).r;
    float combined = blendSubtract_float(blendOverlay_float(leftScrollingNoise, rightScrollingNoise, 1.0), specularNoise, 1.0);
    return step(specularThreshold, combined) * specularColor;
}

vec4 foam(vec2 pixelizedCoordinates, vec4 mainTexColor)
{
    vec4 colorizedFoam = texture(foamTexture, pixelizedCoordinates * foamScale) * foamColor;
    float intensity = clamp(mainTexColor.g * mainTexColor.a - foamIntensity, 0.0, 1.0);
    return vec4(colorizedFoam.rgb, colorizedFoam.a * intensity);
}

// -----------------------------
// Main fragment

void main()
{
    vec2 pixelizedCoordinates = pixelizeCoordinates(applyAspectRatio(fragTexCoord));
    vec4 mainTex = texture(texture0, fragTexCoord);
    vec4 depthBasedWaterColor = texture(waterDepthGradient, vec2(1.0 - mainTex.b, 1.0));
    
    vec4 finalCaustics = caustics(pixelizedCoordinates);  
    vec4 finalSpecular = specular(pixelizedCoordinates);
    vec4 finalFoam = foam(pixelizedCoordinates, mainTex);
    
    vec4 waterWithCausticLayer = mix(depthBasedWaterColor, finalCaustics, finalCaustics.a);
    vec4 waterWithCausticAndSpecularLayer = mix(waterWithCausticLayer, finalSpecular, ceil(finalCaustics.a) * finalSpecular.a);
    vec4 waterWithCausticAndSpecularAndFoamLayer = mix(waterWithCausticAndSpecularLayer, finalFoam, finalFoam.a);
    
    float outline = mainTex.a * mainTex.r;
    vec4 finalOutlineColor = outline * outlineColor;
    
    vec4 finalRGBColor = mix(waterWithCausticAndSpecularAndFoamLayer, finalOutlineColor, outline);
    finalColor = vec4(finalRGBColor.rgb, mainTex.b * generalTransparency);
}


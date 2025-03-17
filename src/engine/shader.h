#ifndef SHADER_H
#define SHADER_H

typedef struct {
    Shader shader;
    int resolutionLoc;
    int strengthLoc;
    float strength;
} VignetteShader;

VignetteShader CreateShader(const char* shaderPath, float strength){
    VignetteShader vignetteShader = {0};
    vignetteShader.shader = LoadShader(NULL, shaderPath);

    if (vignetteShader.shader.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load shader: %s", shaderPath);
        return vignetteShader;
    }

    vignetteShader.strength = strength;
    vignetteShader.resolutionLoc = GetShaderLocation(vignetteShader.shader, "resolution");
    vignetteShader.strengthLoc = GetShaderLocation(vignetteShader.shader, "strength");
    Vector2 resolution = { (float)GetScreenWidth(), (float)GetScreenHeight() };
    SetShaderValue(vignetteShader.shader, vignetteShader.resolutionLoc, &resolution, SHADER_UNIFORM_VEC2);
    return vignetteShader;
}

void UpdateShader(VignetteShader* vignetteShader){
    if (vignetteShader->shader.id == 0) return;
    SetShaderValue(vignetteShader->shader, vignetteShader->strengthLoc, &vignetteShader->strength, SHADER_UNIFORM_FLOAT);
    Vector2 resolution = { (float)GetScreenWidth(), (float)GetScreenHeight() };
    SetShaderValue(vignetteShader->shader, vignetteShader->resolutionLoc, &resolution, SHADER_UNIFORM_VEC2);
}

void UnloadVignetteShader(VignetteShader* vignetteShader){
    if (vignetteShader->shader.id == 0) return;
    UnloadShader(vignetteShader->shader);
}

#endif // SHADER_H

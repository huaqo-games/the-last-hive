#ifndef POSTFX_H
#define POSTFX_H

typedef struct {
    Shader shader;
    int resolutionLoc;
    int strengthLoc;
    float strength;
} PostProcessing;

PostProcessing CreatePostFX(const char* shaderPath){
    PostProcessing postFX = {0};
    postFX.shader = LoadShader(NULL, shaderPath);

    if (postFX.shader.id == 0) {
        TraceLog(LOG_ERROR, "Failed to load shader: %s", shaderPath);
        return postFX;
    }

    postFX.strength = 0.0f;
    postFX.resolutionLoc = GetShaderLocation(postFX.shader, "resolution");
    postFX.strengthLoc = GetShaderLocation(postFX.shader, "strength");
    Vector2 resolution = { (float)GetScreenWidth(), (float)GetScreenHeight() };
    SetShaderValue(postFX.shader, postFX.resolutionLoc, &resolution, SHADER_UNIFORM_VEC2);
    return postFX;
}

void UpdatePostFX(PostProcessing *postFX){
    if (postFX->shader.id == 0) return;
    SetShaderValue(postFX->shader, postFX->strengthLoc, &postFX->strength, SHADER_UNIFORM_FLOAT);
    Vector2 resolution = { (float)GetScreenWidth(), (float)GetScreenHeight() };
    SetShaderValue(postFX->shader, postFX->resolutionLoc, &resolution, SHADER_UNIFORM_VEC2);
}

void RenderPostFX(PostProcessing *postFX, RenderTexture2D *target){
    BeginShaderMode(postFX->shader);
        DrawTextureRec(target->texture, (Rectangle){ 0, 0, target->texture.width, -target->texture.height }, (Vector2){ 0, 0 }, WHITE);
    EndShaderMode();
}

void UnloadPostFX(PostProcessing *postFX){
    if (postFX->shader.id == 0) return;
    UnloadShader(postFX->shader);
}

#endif // POSTFX_H

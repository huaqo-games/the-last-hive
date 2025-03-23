#ifndef ASSET_H
#define ASSET_H

typedef struct {
    const char* path;
    float frameWidth;
    float frameHeight;
    float rotation;
} TextureAsset;

typedef struct {
    const char* path;
} ShaderAsset;

typedef struct {
    const char* path;
} SoundtrackAsset;

typedef struct {
    const TextureAsset *textureAssets;
    const ShaderAsset *shaderAssets;
    const SoundtrackAsset *soundtrackAssets;
} Assets;

#endif // ASSET_H

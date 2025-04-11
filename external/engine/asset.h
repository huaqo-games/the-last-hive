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
    const char* path;
} SoundAsset;

typedef struct {
    const TextureAsset *textureAssets;
    const ShaderAsset *shaderAssets;
    const SoundtrackAsset *soundtrackAssets;
    const SoundAsset *soundAssets;
} Assets;

#endif // ASSET_H

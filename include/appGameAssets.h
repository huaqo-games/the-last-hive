#ifndef APPGAMEASSETS_H
#define APPGAMEASSETS_H


typedef enum
{
    POST_FX,
    SHADER_COUNT
} ShaderID;

const ShaderAsset shaderAssets[SHADER_COUNT] = {
    {"shaders/postfx.fs"}};


typedef enum
{
    BEE_AMBIENT,
    SOUNDTRACK_COUNT
} SoundtrackID;

const SoundtrackAsset soundtrackAssets[SOUNDTRACK_COUNT] = {
    {"assets/sea.mp3"}};


#endif // APPGAMEASSETS_H

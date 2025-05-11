#ifndef GAMEASSETS_H
#define GAMEASSETS_H
#include <asset.h>

typedef enum
{
    MAP_TILED,
    MAP_LDTK,
    MAP_LDTK_PNG,
    MAP_COUNT
} MapID;

const MapAsset mapAssets[MAP_COUNT] = {
    { "assets/map.tmx" },
    { "assets/map.json" },
    { "assets/SunnyLand_by_Ansimuz.png" }
};

////////////////////////////////////////////////////////////////////////////

typedef enum
{
    PLAYER,
    PLAYER_ACTIONS,
    TOOLS,
    FLOWER,
    BEE,
    GRASS,
    HIVE,
    CURSOR,
    TEX_COUNT
} TextureID;

const TextureAsset textureAssets[TEX_COUNT] = {
    {"assets/SproutLandsBasic/Characters/character.png", 48.0f, 48.0f, 0.0f},
    {"assets/SproutLandsBasic/Characters/BasicCharakterActions.png", 48.0f, 48.0f, 0.0f},
    {"assets/SproutLandsBasic/Objects/tools.png", 48.0f, 16.0f, 0.0f},
    {"assets/carrot_and_tomato.png", 32.0f, 32.0f, 0.0f},
    {"assets/character_bee.png", 16.0f, 16.0f, 0.0f},
    {"assets/grass.png", 16.0f, 16.0f, 0.0f},
    {"assets/hive.png", 32.0f, 32.0f, 0.0f},
    {"assets/SproutLandsUI/Spritesheets/Mouse sprites/TriangleMouseicon1.png", 16.0f, 16.0f, 0.0f}};

////////////////////////////////////////////////////////////////////////////

typedef enum
{
    POST_FX,
    SHADER_COUNT
} ShaderID;

const ShaderAsset shaderAssets[SHADER_COUNT] = {
    {"shaders/postfx.fs"}
};

////////////////////////////////////////////////////////////////////////////

typedef enum
{
    BEE_AMBIENT,
    BACKGROUND_MUSIC,
    SOUNDTRACK_COUNT
} SoundtrackID;

const SoundtrackAsset soundtrackAssets[SOUNDTRACK_COUNT] = {
    {"assets/beez.mp3"},
    {"assets/audio/sounds/bg.mp3"}
};

////////////////////////////////////////////////////////////////////////////

#endif // GAMEASSETS_H

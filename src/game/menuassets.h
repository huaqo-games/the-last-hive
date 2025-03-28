#ifndef MENUASSETS_H
#define MENUASSETS_H
#include "../engine/asset.h"

typedef enum {
    MENU_CURSOR_TEX,
    MENU_BIG_BUTTONS_TEX,
    MENU_BOARD_TEX,
    MENU_CLOUD_BACKGROUND,
    MENU_CLOUD_MIDGROUND,
    MENU_CLOUD_FOREGROUND,
    MENU_TEX_COUNT
} MenuTextureID;

const TextureAsset menuTextureAssets[MENU_TEX_COUNT] = {
    {"assets/SproutLandsUI/Spritesheets/Mouse sprites/TriangleMouseicon1.png", 16.0f, 16.0f, 0.0f },
    {"assets/SproutLandsUI/Spritesheets/UIBigPlayButtonHover.png", 96.0f, 32.0f, 0.0f},
    {"assets/SproutLandsUI/Spritesheets/Settingmenu.png", 128.0f, 144.0f, 0.0f},
    {"assets/Clouds/Clouds1/1.png", 576.0f, 324.0f, 0.0f},
    {"assets/Clouds/Clouds1/2.png", 576.0f, 324.0f, 0.0f},
    {"assets/Clouds/Clouds1/4.png", 576.0f, 324.0f, 0.0f}
};

typedef enum {
    MENU_MUSIC,
    MENU_SOUNDTRACK_COUNT
} MenuSoundtrackID;

const SoundtrackAsset menuSoundtrackAssets[MENU_SOUNDTRACK_COUNT] = {
    {"assets/merrygoround.wav"}
};

typedef enum {
    HOVER_SOUND,
    CLICK_SOUND,
    MENU_SOUND_COUNT
} MenuSoundID;

const SoundAsset menuSoundAssets[MENU_SOUND_COUNT] = {
    {"assets/audio/WAV/Minimalist1.wav"},
    {"assets/audio/WAV/Abstract1.wav"}
};

#endif // MENUASSETS_H

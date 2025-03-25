#ifndef MENUASSETS_H
#define MENUASSETS_H
#include "../engine/asset.h"

typedef enum {
    BIG_BUTTONS,
    BOARD,
    MENU_TEX_COUNT
} MenuTextureID;

const TextureAsset menuTextureAssets[MENU_TEX_COUNT] = {
    {"assets/SproutLandsUI/Spritesheets/UIBigPlayButton.png", 96.0f, 32.0f, 180.0f},
    {"assets/SproutLandsUI/Spritesheets/Settingmenu.png", 128.0f, 144.0f, 180.0f},
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

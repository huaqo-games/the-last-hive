#ifndef APPMENUASSETS_H
#define APPMENUASSETS_H

typedef enum
{
    MENU_CURSOR_TEX,
    MENU_BIG_BUTTONS_TEX,
    MENU_BOARD_TEX,
    MENU_CLOUD_BACKGROUND,
    MENU_CLOUD_MIDGROUND,
    MENU_CLOUD_FOREGROUND,
    MENU_TEX_COUNT
} MenuTextureID;

const TextureAsset menuTextureAssets[MENU_TEX_COUNT] = {
    {"assets/mouse.png", 16.0f, 16.0f, 0.0f},
    {"assets/buttons.png", 288.0f/3, 96.0f/3, 0.0f},
    {"assets/menu_board.png", 128.0f, 144.0f, 0.0f},
    {"assets/cloud_background.png", 576.0f, 324.0f, 0.0f},
    {"assets/cloud_midground.png", 576.0f, 324.0f, 0.0f},
    {"assets/cloud_foreground.png", 576.0f, 324.0f, 0.0f}};

typedef enum
{
    MENU_MUSIC,
    MENU_SOUNDTRACK_COUNT
} MenuSoundtrackID;

const SoundtrackAsset menuSoundtrackAssets[MENU_SOUNDTRACK_COUNT] = {
    {"assets/merrygoround.wav"}};

typedef enum
{
    HOVER_SOUND,
    CLICK_SOUND,
    MENU_SOUND_COUNT
} MenuSoundID;

const SoundAsset menuSoundAssets[MENU_SOUND_COUNT] = {
    {"assets/button_hover.wav"},
    {"assets/button_click.wav"}};

#endif // APPMENUASSETS_H

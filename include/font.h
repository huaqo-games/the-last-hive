#ifndef FONT_H
#define FONT_H

void InitFont(Font *font){
    *font = LoadFont("assets/SproutLandsUI/fonts/pixelFont-7-8x14-sproutLands.fnt");
    SetTextureFilter(font->texture, TEXTURE_FILTER_POINT);
}

void CleanupFont(Font *font){
    UnloadFont(*font);
}

#endif //FONT_H

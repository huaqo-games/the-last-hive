#ifndef FONT_H
#define FONT_H

void InitFont(Font *font, const char* path){
    *font = LoadFont(path);
    SetTextureFilter(font->texture, TEXTURE_FILTER_POINT);
}

void CleanupFont(Font *font){
    UnloadFont(*font);
}

#endif //FONT_H

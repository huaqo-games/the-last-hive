#include "engine.h"

void InitFont(Font *font, const char* path){
    *font = LoadFont(path);
    SetTextureFilter(font->texture, TEXTURE_FILTER_POINT);
}

void CleanupFont(Font *font){
    UnloadFont(*font);
}


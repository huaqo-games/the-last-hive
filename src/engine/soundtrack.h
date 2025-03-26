#ifndef SOUNDTRACK_H
#define SOUNDTRACK_H

typedef struct {
    Music music;
    bool playing;
} Soundtrack;

Soundtrack LoadSoundtrack(const char* musicPath){
    Soundtrack soundtrack = {
        .music = LoadMusicStream(musicPath),
        .playing = 0
    };
    PlayMusicStream(soundtrack.music);
    return soundtrack; 
}

void UpdateSoundtrack(Soundtrack *soundtrack){
    UpdateMusicStream(soundtrack->music);
}

#endif // SOUNDTRACK_H


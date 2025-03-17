#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

typedef struct {
    Music music;
    bool playing;
} MyMusic;

MyMusic CreateMusic(char* musicPath){
    MyMusic music = {
        .music = LoadMusicStream(musicPath),
        .playing = 0
    };
    PlayMusicStream(music.music);
    return music; 
}

void UpdateMusic(MyMusic* music){
    UpdateMusicStream(music->music);
}

#endif // MUSICMANAGER_H


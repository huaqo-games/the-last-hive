#ifndef SOUNDTRACK_H
#define SOUNDTRACK_H

typedef struct {
    Music music;
    bool playing;
	bool paused;
} Soundtrack;

Soundtrack LoadSoundtrack(const char* musicPath){
    Soundtrack soundtrack = {
        .music = LoadMusicStream(musicPath),
        .playing = false,
		.paused = false
    };
    PlayMusicStream(soundtrack.music);
    return soundtrack; 
}

void UpdateSoundtrack(Soundtrack *soundtrack, bool playing){

	if (playing && !soundtrack->playing){
		ResumeMusicStream(soundtrack->music);
		soundtrack->paused = false;
	} else if (!playing && soundtrack->playing){
		PauseMusicStream(soundtrack->music);
		soundtrack->paused = true;
	}

	soundtrack->playing = playing;

	if (soundtrack->playing) {
		UpdateMusicStream(soundtrack->music);
	}

}

#endif // SOUNDTRACK_H


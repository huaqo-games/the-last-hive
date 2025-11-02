#include "engine.h"

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


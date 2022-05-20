#pragma once

#include <SDL_mixer.h>

#include "init.h"
class Audio
{
public:
	Audio();
	//The music that will be played
	Mix_Music* gMusic;

	//The sound effects that will be used
	Mix_Chunk* gMove;
	Mix_Chunk* gRotate;
	Mix_Chunk* gDrop;
	Mix_Chunk* gClear;
	Mix_Chunk* gGameOver;

	bool loadAudio();
	void deleteAudio();
	void playMusic();
	void pauseOrResumeMusic();
	void playSoundEffect();

	Mix_Music* currentMusic;
	Mix_Chunk* currentSoundEffect;
};


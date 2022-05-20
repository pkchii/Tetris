#include "audio.h"


Audio::Audio()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

bool Audio::loadAudio()
{
    bool success = true;
    //Load music
    gMusic = Mix_LoadMUS("assets/music.wav");
    if (gMusic == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    currentMusic = gMusic;

    //Load sound effects
    gMove = Mix_LoadWAV("assets/move.wav");
    if (gMove == NULL)
    {
        printf("Failed to load move sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gRotate = Mix_LoadWAV("assets/rotate.wav");
    if (gRotate == NULL)
    {
        printf("Failed to load rotate sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gDrop = Mix_LoadWAV("assets/drop.wav");
    if (gDrop == NULL)
    {
        printf("Failed to load drop sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gClear = Mix_LoadWAV("assets/clear_line.wav");
    if (gClear == NULL)
    {
        printf("Failed to load clear sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gGameOver = Mix_LoadWAV("assets/game_over.wav");
    if (gGameOver == NULL)
    {
        printf("Failed to load game over sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    return success;
}

void Audio::deleteAudio()
{
    /*Mix_FreeChunk(gMove);
    Mix_FreeChunk(gRotate);
    Mix_FreeChunk(gDrop);
    Mix_FreeChunk(gClear);
    Mix_FreeChunk(gGameOver);
    Mix_FreeChunk(currentSoundEffect);

    gMove = NULL;
    gRotate = NULL;
    gDrop = NULL;
    gClear = NULL;
    gGameOver = NULL;
    currentSoundEffect = NULL;*/
    Mix_CloseAudio();
}

void Audio::playMusic()
{
    Mix_PlayMusic(currentMusic, -1);
}

void Audio::pauseOrResumeMusic()
{
    //If the music is paused
    if (Mix_PausedMusic() == 1)
    {
        //Resume the music
        Mix_ResumeMusic();
    }
    //If the music is playing
    else
    {
        //Pause the music
        Mix_PauseMusic();
    }
}

void Audio::playSoundEffect()
{
    Mix_PlayChannel(-1, currentSoundEffect, 0);
}

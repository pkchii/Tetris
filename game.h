#pragma once
#include <iostream>
#include <string>

#include <windows.h>

#include <SDL.h>
#include <SDL_ttf.h>

#include "board.h"
#include "config.h"
#include "gamestate.h"
#include "init.h"
#include "inputmanager.h"
#include "menustate.h"
#include "renderer.h"
#include "texture.h"
#include "pausestate.h"
#include "highscoreState.h"

extern SDL_Window* gWindow;
extern Texture tetrominoSprites;


class Game
{
public:
	bool gameInitialize();
	void run();
	State runGamestate();
	State runMenustate();
	State runHighscoreState();
	void exit();

	State currentState = menu;
private:
	InputManager* inManager = new InputManager;
	Menustate* menustate;
	GameState* gamestate;
	HighscoreState* highscoreState;
	Renderer renderer;
	
};


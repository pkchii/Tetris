#pragma once
#include <iostream>
#include <vector>

#include "texture.h"
#include "inputManager.h"
#include "renderer.h"
#include "button.h"
#include "config.h"

const int quitButtonIndex = 0;
const int resumeButtonIndex = 1;


class Pausestate
{
public:
	~Pausestate();
	void initialize();
	void run();
	void update();
	void draw();

	State next_state = pause;
private:
	std::vector<Button*> mButtons;
	Texture* paused_frame;
	InputManager* inManager = new InputManager;
	Renderer* mRenderer;
};


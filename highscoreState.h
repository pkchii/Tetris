#pragma once

#include <iostream>
#include <vector>

#include "texture.h"
#include "inputManager.h"
#include "renderer.h"
#include "button.h"
#include "config.h"
#include "score.h"

class HighscoreState
{
public:
	~HighscoreState();
	void initialize();
	void run();
	void update();
	void draw();
	void drawScore(std::string score, int x, int y);

	State next_state = highscore;
private:
	Score* score = new Score;
	std::vector<Texture*> mScoreText;
	Button* quitButton;
	InputManager* inManager = new InputManager;
	Renderer* mRenderer;
};


#pragma once
#include <iostream>
#include <vector>

#include "texture.h"
#include "inputManager.h"
#include "renderer.h"
#include "button.h"
#include "config.h"

const int playButtonIndex = 0;
const int highscoresButtonIndex = 1;
const int exitButtonIndex = 2;

class Menustate
{
public:
	~Menustate();
	void initialize();
	void run();
	void update();
	void draw();

	State next_state = menu;
private:
	std::vector<Button*> mButtons;
	Texture* title_text;
	int index;                          // Shows the current button selected
	InputManager* inManager = new InputManager;
	Renderer* mRenderer;
};


#include "highscoreState.h"

HighscoreState::~HighscoreState()
{
	delete quitButton;
	for (auto i : mScoreText) {
		i->free();
	}
	delete inManager;
	delete mRenderer;
	score->~Score();
	delete score;
}

void HighscoreState::initialize()
{
	quitButton = new Button("assets/button-quit.png", (config::logical_window_width - 80) / 2, 280);
}

void HighscoreState::run()
{
	update();
	draw();
}

void HighscoreState::update()
{
	SDL_Event event;
	if (SDL_PollEvent(&event) != 0) {
		quitButton->handleEvent(event);
		if (quitButton->selected) {
			next_state = menu;
		}
	}
}

void HighscoreState::draw()
{
	mRenderer->clearScreen();
	drawScore("HIGH SCORES", config::logical_window_width / 2, 50);
	int y0 = 100, distance = 30;
	for (auto i : score->stringHighScores) {
		drawScore(i, config::logical_window_width / 2, y0);
		y0 = y0 + distance;
	}
	quitButton->draw();
	mRenderer->updateScreen();
}

void HighscoreState::drawScore(std::string score, int x, int y)
{
	Texture* highscoreText = new Texture;
	highscoreText->loadFromText(score, config::default_text_color);
	highscoreText->renderCentered(x, y);
	highscoreText->free();
}


#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>

#include "config.h"
#include "texture.h"

const std::string scoreFile = "scores.txt";

class Score
{
public:
	Score();
	~Score();
	void update(int lineDeleted);
	void updateUserScore(int lineDeleted);
	void updateHighestScore();
	void updateData();
	int getCurrentWaitTime();
	void drawCurrentScore();
	void drawHighestScore();
	std::string convertToString(int number);
	std::vector <int> getData();
	std::vector <std::string> stringHighScores; // high scores converted to string
private:
	int currentScore = 0;
	int highScore;
	int waitTime = config::wait_time_default;
	std::string userScore = "your score: 0"; // current score converted to string
	std::string highestScore = "high score: "; // highest score converted to string
	std::vector <int> highScores;
	Texture* scoreTexture = new Texture;
};


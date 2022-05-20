#include "Score.h"

using namespace std;
Score::Score()
{
	highScores = getData();
	highScore = highScores.at(0);
	highestScore = "high score: " + convertToString(highScore);
	for (int i = 0; i < 5; i++) {
		string s = to_string(highScores.at(i));
		stringHighScores.push_back(s);
	}
}
Score::~Score()
{
	scoreTexture->free();

}

void Score::update(int lineDeleted)
{
	int tmp = lineDeleted;
	updateUserScore(tmp);
	waitTime = getCurrentWaitTime();
	updateHighestScore();
}

void Score::updateUserScore(int lineDeleted)
{
	currentScore = lineDeleted * 100;
	userScore = "your score: " + convertToString(currentScore);
}

void Score::updateHighestScore()
{
	if (currentScore > highScore) {
		highScore = currentScore;
	}
	highestScore = "high score: " + convertToString(highScore);
}

void Score::updateData()
{
	ofstream outFile(scoreFile.c_str(), ios::app);
	outFile << currentScore << endl;
	outFile.close();
}


int Score::getCurrentWaitTime()
{
	int tmp = currentScore / 1000;
	int currentWaitTime = config::wait_time_default - tmp*100;
	if (currentWaitTime < 100) return 100;
	return currentWaitTime;
}

void Score::drawCurrentScore()
{
	scoreTexture = new Texture;
	scoreTexture->loadFromText(userScore, config::default_text_color);
	scoreTexture->render(10, 10);
	scoreTexture->free();
}

void Score::drawHighestScore()
{
	scoreTexture = new Texture;
	scoreTexture->loadFromText(highestScore, config::default_text_color);
	scoreTexture->render(10, 40);
	scoreTexture->free();
}

string Score::convertToString(int number)
{
	return to_string(number);
}

vector<int> Score::getData()
{
	vector<int> tmp;
	ifstream inFile(scoreFile.c_str());
	int number;
	while (!inFile.eof()) {
		inFile >> number;
		tmp.push_back(number);
	}
	inFile.close();
	sort(tmp.rbegin(), tmp.rend());
	return tmp;
}

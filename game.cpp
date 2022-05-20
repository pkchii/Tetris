#include "game.h"


bool Game::gameInitialize()
{
    return initialize();
}

void Game::run()
{
    State updateState = currentState;
    switch (currentState) {
    case menu:
    {
        menustate = new Menustate;
        updateState = runMenustate();
        break;
    }
    case gameplay: case playagain:
    {
        gamestate = new GameState;
        updateState = runGamestate();
        break;
    }
    case highscore:
    {
        highscoreState = new HighscoreState;
        updateState = runHighscoreState();
        break;
    }
    }
    currentState = updateState;
}

State Game::runGamestate()
{
    loadMedia();
    gamestate->initializeState();
    inManager->clearEventQueue();
    while (gamestate->next_state == gameplay) {
        gamestate->run();
    }
    gamestate->~GameState();
    State result = gamestate->next_state;
    gamestate = NULL;
    return result;
}

State Game::runMenustate()
{
    loadMedia();
    menustate->initialize();
    inManager->clearEventQueue();
    while (menustate->next_state == menu) {
        menustate->run();
    }
    menustate->~Menustate();
    State result = menustate->next_state;
    menustate = NULL;
    return result;
}

State Game::runHighscoreState()
{
    loadMedia();
    highscoreState->initialize();
    inManager->clearEventQueue();
    while (highscoreState->next_state == highscore) {
        highscoreState->run();
    }
    highscoreState->~HighscoreState();
    State result = highscoreState->next_state;
    highscoreState = NULL;
    return result;
}

void Game::exit()
{
    delete inManager;
    delete menustate;
    delete gamestate;
    delete highscoreState;
    std::cerr << "Now exiting!\n";
    close();
}

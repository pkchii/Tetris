#include "menustate.h"


Menustate::~Menustate()
{
    for (auto i : mButtons)
    {
        delete i;
    }
    title_text->free();
    delete inManager;
    delete mRenderer;
}

void Menustate::initialize()
{
    index = 0;
    title_text = new Texture();
    title_text->loadFromText("Tetris", config::default_text_color);

    mButtons.push_back(new Button("assets/button-play.png", (config::logical_window_width - 80) / 2, 130));
    mButtons.push_back(new Button("assets/button-highscores.png", (config::logical_window_width - 80) / 2, 180));
    mButtons.push_back(new Button("assets/button-exit.png", (config::logical_window_width - 80) / 2, 230));
}

void Menustate::run()
{
    update();
    draw();
}

void Menustate::update()
{
    SDL_Event event;
    if (SDL_PollEvent(&event) != 0) {
        int tempIndex = -1; // get index of the selected button
        for (auto i : mButtons) {
            tempIndex++;
            i->handleEvent(event);
            if (i->selected) {
                switch (tempIndex) {
                case playButtonIndex:
                {
                    next_state = gameplay;
                    break;
                }
                case highscoresButtonIndex:
                {
                    next_state = highscore;
                    break;
                }
                case exitButtonIndex:
                {
                    next_state = exit_game;
                    break;
                }
                }
                break;
            }
        }
    }
}

void Menustate::draw()
{
    mRenderer->clearScreen();
    for (auto i : mButtons)
    {
        i->draw();
    }
    title_text->renderCentered(config::logical_window_width / 2, 50);
    mRenderer->updateScreen();
}

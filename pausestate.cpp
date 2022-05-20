#include "pausestate.h"

Pausestate::~Pausestate()
{

    for (auto i : mButtons)
    {
        delete i;
    }
    paused_frame->free();
    delete inManager;
    delete mRenderer;
}

void Pausestate::initialize()
{
    paused_frame = new Texture();
    paused_frame->loadFromImage("assets/paused-frame.png");
    mButtons.push_back(new Button("assets/button-quit.png", 230, 190));
    mButtons.push_back(new Button("assets/button-resume.png", 330, 190));
}

void Pausestate::run()
{
    update();
    draw();
}

void Pausestate::update()
{
    SDL_Event event;
    if (SDL_PollEvent(&event) != 0) {
        int tempIndex = -1; // get index of the selected button
        for (auto i : mButtons) {
            tempIndex++;
            i->handleEvent(event);
            if (i->selected) {
                switch (tempIndex) {
                case quitButtonIndex:
                {
                    next_state = menu;
                    break;
                }
                case resumeButtonIndex:
                {
                    next_state = gameplay;
                    break;
                }
                }
                break;
            }
        }
    }
}

void Pausestate::draw()
{
    //mRenderer->clearScreen();
    paused_frame->renderCentered(config::logical_window_width / 2, config::logical_window_height / 2);
    for (auto i : mButtons)
    {
        i->draw();
    }
    mRenderer->updateScreen();
}

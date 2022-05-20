#include "texture.h"
#include "config.h"
#include <SDL.h>

#pragma once
class Button
{
public:
    Button(std::string path, int posX = 0, int posY = 0);
    ~Button();
    void draw();
    void handleEvent(SDL_Event e);
    int getX();
    int getY();
    int getWidth();
    int getHeight();

    bool selected = false;
private:
    int position_x;
    int position_y;
    int width;
    int height;
    Texture* texture;
    bool transparent = false;
};


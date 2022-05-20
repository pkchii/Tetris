#include "button.h"

Button::Button(std::string path, int posX, int posY)
{
    position_x = posX;
    position_y = posY;
    texture = new Texture;
    texture->loadFromImage(path);
    width = texture->getWidth();
    height = texture->getHeight();
}

Button::~Button()
{
    texture->free();
}

void Button::draw()
{
    if (transparent) {
        texture->setAlphaMode(config::transparency_alpha);
    }
    texture->render(position_x, position_y);
    texture->setAlphaMode(255);
}

void Button::handleEvent(SDL_Event e)
{
    if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if (x < position_x)
        {
            inside = false;
        }
        //Mouse is right of the button
        else if (x > position_x + width)
        {
            inside = false;
        }
        //Mouse above the button
        else if (y < position_y)
        {
            inside = false;
        }
        //Mouse below the button
        else if (y > position_y + height)
        {
            inside = false;
        }
        if (inside) {
            transparent = true;
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                selected = true;
            }
            else {
                selected = false;
            }
        }
        else {
            transparent = false;
            selected = false;
        }
    }
}

int Button::getX()
{
    return position_x;
}

int Button::getY()
{
    return position_y;
}

int Button::getWidth()
{
    return width;
}

int Button::getHeight()
{
    return height;
}
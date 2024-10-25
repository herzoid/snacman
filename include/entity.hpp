#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "math.hpp"

class Entity
{
public:
    Entity(Vect2f pos);
    Vect2f &get_pos();
    SDL_Texture *get_texture();
    SDL_Rect getCurFrame();
private:
    double x, y;
    SDL_Rect curFrame;
    SDL_Texture *tex;
    Vect2f pos;
};

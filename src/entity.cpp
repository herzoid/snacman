#include "../include/entity.hpp"

Entity::Entity(Vect2f pPos)
    : pos(pPos)
{
    curFrame.x = 0;
    curFrame.y = 0;
    curFrame.w = 48;
    curFrame.h = 48;
}

Vect2f &Entity::get_pos()
{
    return pos;
}

SDL_Texture *Entity::get_texture()
{
    return tex;
}

SDL_Rect Entity::getCurFrame()
{
    return curFrame;
}

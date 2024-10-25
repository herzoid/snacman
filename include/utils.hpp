#pragma once

#include <SDL2/SDL.h>

// Movement directions
enum moveDirection
{
    TO_UP,
    TO_DOWN,
    TO_LEFT,
    TO_RIGHT
};

// Turning directions type
enum turnDirection
{
    FROM_UP_TO_LEFT,
    FROM_UP_TO_RIGHT,
    FROM_DOWN_TO_LEFT,
    FROM_DOWN_TO_RIGHT,
    FROM_LEFT_TO_UP,
    FROM_LEFT_TO_DOWN,
    FROM_RIGHT_TO_UP,
    FROM_RIGHT_TO_DOWN
};

namespace utils
{
    inline float hireTimeInSec()
    {
        float t = SDL_GetTicks64();
        t *= 0.001f;
        return t;
    }
} // namespace utils

#include "../include/eHandler.hpp"

void eHandler::key_handling()
{
    switch (event->key.keysym.sym)
    {
    case SDLK_ESCAPE:
        Quit = true;
        break;

    default:
        break;
    }
}

eHandler::eHandler() : Quit(false)
{
}

eHandler::~eHandler()
{
}

void eHandler::poll_events(SDL_Event *e)
{
    event = e;
    while (SDL_PollEvent(event))
    {
        switch (event->type)
        {
        case SDL_QUIT:
            /* code */
            break;
        case SDL_KEYDOWN:
            key_handling();
            break;

        default:
            break;
        }
    }
}

bool eHandler::exit()
{
    return Quit;
}

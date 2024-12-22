#include "../include/eHandler.hpp"
#include "eHandler.hpp"

void EventHandler::keypress_handling()
{
    switch (event->key.keysym.sym)
    {
    case SDLK_ESCAPE:
        quit = true;
        break;

    case SDLK_RIGHT:
        // Check current direction and set new
        if (entity->get_seg_dir(0) != TO_LEFT && entity->get_seg_dir(0) != TO_RIGHT)
        {
            if (abs(entity->get_seg_pos(0).y - entity->get_seg_pos(1).y) >= (entity->get_seg_interval() * entity->get_flexRatio()))
            {
                entity->mov.direction == TO_UP ? entity->mov.turn = FROM_DOWN_TO_RIGHT : entity->mov.turn = FROM_UP_TO_RIGHT;
                entity->mov.direction = TO_RIGHT;
                entity->set_head_direction(TO_RIGHT);
                entity->fix_turn_data();
                // Reset coordinates fixation
                entity->mov.coordSet = 0;
            }
        }
        break;
    case SDLK_LEFT:
        // Check current direction and set new
        if (entity->mov.direction != TO_RIGHT && entity->mov.direction != TO_LEFT)
        {
            if (abs(entity->get_seg_pos(0).y - entity->get_seg_pos(1).y) >= (entity->get_seg_interval() * entity->get_flexRatio()))
            {
                entity->mov.direction == TO_UP ? entity->mov.turn = FROM_DOWN_TO_LEFT : entity->mov.turn = FROM_UP_TO_LEFT;
                entity->mov.direction = TO_LEFT;
                entity->set_head_direction(TO_LEFT);
                entity->fix_turn_data();
                // Reset coordinates fixation
                entity->mov.coordSet = 0;
            }
        }
        break;
    case SDLK_UP:
        // Check current direction and set new
        if (entity->mov.direction != TO_DOWN && entity->mov.direction != TO_UP)
        {
            if (abs(entity->get_seg_pos(0).x - entity->get_seg_pos(1).x) >= (entity->get_seg_interval() * entity->get_flexRatio()))
            {
                entity->mov.direction == TO_LEFT ? entity->mov.turn = FROM_RIGHT_TO_UP : entity->mov.turn = FROM_LEFT_TO_UP;
                entity->mov.direction = TO_UP;
                entity->set_head_direction(TO_UP);
                entity->fix_turn_data();
                // Reset coordinates fixation
                entity->mov.coordSet = 0;
            }
        }
        break;
    case SDLK_DOWN:
        // Check current direction and set new
        if (entity->mov.direction != TO_UP && entity->mov.direction != TO_DOWN)
        {
            if (abs(entity->get_seg_pos(0).x - entity->get_seg_pos(1).x) >= (entity->get_seg_interval() * entity->get_flexRatio()))
            {
                entity->mov.direction == TO_LEFT ? entity->mov.turn = FROM_RIGHT_TO_DOWN : entity->mov.turn = FROM_LEFT_TO_DOWN;
                entity->mov.direction = TO_DOWN;
                entity->set_head_direction(TO_DOWN);
                entity->fix_turn_data();
                // Reset coordinates fixation
                entity->mov.coordSet = 0;
            }
        }
        break;

    case SDLK_p:
        entity->add_segment();
        break;

    case SDLK_f:
        if (!screenMode)
        {
            screenMode = SDL_WINDOW_FULLSCREEN;
        }
        else
            screenMode = 0;
        break;

    default:
        break;
    }
}

EventHandler::EventHandler() : quit(false), screenMode(0)
{
}

EventHandler::~EventHandler()
{
}

void EventHandler::poll_events(SDL_Event *e)
{
    event = e;
    while (SDL_PollEvent(event))
    {
        switch (event->type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            keypress_handling();
            break;

        default:
            break;
        }
    }
}

void EventHandler::manage_entity(Entity *ent)
{
    entity = ent;
}
int EventHandler::get_screen_mode()
{
    return screenMode;
}
bool EventHandler::exit()
{
    return quit;
}

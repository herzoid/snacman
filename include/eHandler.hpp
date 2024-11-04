#pragma once
#include <SDL2/SDL.h>
#include "entity.hpp"

class EventHandler
{
private:
    SDL_Event *event;
    bool quit;
    // Movement *mov;
    Entity *entity;

    void keypress_handling();

public:
    EventHandler();
    ~EventHandler();
    void poll_events(SDL_Event *e);
    // void eval_direction(Movement *mv);
    void manage_entity(Entity *ent);
    template <typename myType> void input_handle(myType *mt);
    bool exit();
};

template <typename myType>
inline void EventHandler::input_handle(myType *mt)
{
    
}

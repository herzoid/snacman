#include <SDL2/SDL.h>
#include "utils.hpp"

class eHandler
{
private:
    SDL_Event *event;
    bool Quit;

    void key_handling();

public:
    eHandler();
    ~eHandler();
    void poll_events(SDL_Event *e);
    bool exit();
};



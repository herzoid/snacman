#include <iostream>
#include <SDL2/SDL.h>

#include <random>
#include <cmath>
#include <sstream>
#include <iomanip>

#include "../include/canvas.hpp"
#include "../include/entity.hpp"
#include "../include/eHandler.hpp"

#define FONTNAME "/usr/share/fonts/TTF/DejaVuSansMono.ttf"

int main(int argc, char const *argv[])
{
    // std::cout << argv[0] << "\n";

    int dp = 1;
    const int scrW = 1024;
    const int scrH = 768;
    const int maxRGB = 255;

    float p = (float)maxRGB / (float)scrW;
    Canvas newCanvas("SDL test", scrW, scrH);

    if (newCanvas.is_init())
    {
        // Get display mode
        SDL_DisplayMode dm;
        SDL_Event e;

        EventHandler eHandler;

        // SDL_TextInputEvent te;
        Vect2f crd, crd2, fixedCrd;
        crd.x = 100;
        crd.y = 100;

        int r = 255;
        int g = 255;
        int b = 255;
        bool quit = false;

        // Movement move;

        Entity snake = Entity();

        // Main loop
        while (!quit)
        {
            Uint64 frameStart = SDL_GetTicks64();
            Uint64 frameCount;

            eHandler.poll_events(&e);
            eHandler.manage_entity(&snake);
            quit = eHandler.exit();
            SDL_SetWindowFullscreen(newCanvas.get_window(), eHandler.get_screen_mode());

            SDL_GetWindowDisplayMode(newCanvas.get_window(), &dm);
            snake.detect_display_mode(&dm);

            newCanvas.set_color(r, g, b, 255);

            // snake.calc_seg_position();
            snake.calc_segment_pos();

            newCanvas.render_entity(&snake, r, g, b, 255);

            snake.generate_food_position();
            newCanvas.render_circle(snake.get_food_pos(), 3, r, g, b, 255);

            snake.find_the_food();

            // Vect2f crdBox(100, 200);
            // newCanvas.render_rbox(crdBox, 10, 0, r, g, b, 255);

            newCanvas.redraw();
            newCanvas.clear();

            // Time in ms for 1 frame
            Uint64 frameTime = SDL_GetTicks64() - frameStart;

            if (frameTime < 1000 / 60)
            {
                SDL_Delay(1000 / 60 - frameTime);
            }

            frameTime = SDL_GetTicks64() - frameStart;

            double FPS = 1 / static_cast<double>(frameTime) * 1000;

            std::stringstream graphInfo;
            graphInfo << dm.w << "x" << dm.h
                      << " Time from start (ms) " << frameStart
                      << " ms/frame " << frameTime
                      << " FPS " << static_cast<int>(FPS)
                      << " Frames from start " << ++frameCount;
            std::stringstream crdInfo;

            crdInfo << "x=" << snake.get_seg_pos(0).x
                    << " y=" << snake.get_seg_pos(0).y;

            int ht = newCanvas.render_text(0, 0, FONTNAME, 14, graphInfo.str(), {255, 255, 255, 0}, {0, 0, 0, 0}).h;
            newCanvas.render_text(0, ht, FONTNAME, 14, crdInfo.str(), {255, 255, 255, 0}, {0, 0, 0, 0});
        }

        std::cout << "Canvas created"
                  << "\n";
        return 0;
    }
    else
    {
        std::cout << "Error!!! "
                  << SDL_GetError()
                  << "\n";
        return 1;
    }
}

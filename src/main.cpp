#include <iostream>
// #include <SDL3/SDL.h>
#include <SDL2/SDL.h>

#include <random>
#include <cmath>
#include <sstream>
#include <iomanip>

#include "../include/canvas.hpp"
#include "../include/entity.hpp"
#include "../include/eHandler.hpp"
#include "../include/sound.hpp"

#define FONTNAME "/usr/share/fonts/TTF/DejaVuSansMono.ttf"
#define adjustedFPS 60

int main(int argc, char const *argv[])
{
    // std::cout << argv[0] << "\n";

    const int scrW = 1024;
    const int scrH = 768;
    const int maxRGB = 255;

    float p = (float)maxRGB / (float)scrW;
    Canvas newCanvas("SDL test", scrW, scrH);
    sound sndEng;

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

        sndEng.open_snd_device();

        bool enbSnd;

        // Main loop
        while (!quit)
        {
            // sndEng.play_sound();
            // Frame start time
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
            // newCanvas.render_lent(&snake);

            snake.generate_food_position();
            newCanvas.render_circle(snake.get_food_pos(), 3, r, g, b, 255);

            if (snake.grab_the_food(sndEng))
            {
                sndEng.play_sound(440);
                sndEng.play_sound(880);
            }

            // Vect2f crdBox(100, 200);
            // newCanvas.render_rbox(crdBox, 10, 0, r, g, b, 255);

            newCanvas.redraw();
            newCanvas.clear();

            // Time in ms for 1 frame
            Uint64 frameTime = SDL_GetTicks64() - frameStart;

            if (frameTime < 1000 / adjustedFPS)
            {
                SDL_Delay(1000 / adjustedFPS - frameTime);
            }

            frameTime = SDL_GetTicks64() - frameStart;

            double realFPS = 1 / static_cast<double>(frameTime) * 1000;

            std::stringstream graphInfo;
            graphInfo << dm.w << "x" << dm.h
                      << " Time from start (ms) " << frameStart
                      << " ms/frame " << frameTime
                      << " FPS " << static_cast<int>(realFPS)
                      << " Frames from start " << ++frameCount;
            std::stringstream crdInfo;

            int ht = newCanvas.render_text(0, 0, FONTNAME, 14, graphInfo.str(), {255, 255, 255, 0}, {0, 0, 0, 0}).h;

            for (size_t i = 0; i < snake.get_segs_num(); i++)
            {
                if (i == 0)
                {
                    crdInfo << "segments=" << snake.get_segs_num();
                    ht = ht + newCanvas.render_text(0, ht, FONTNAME, 10, crdInfo.str(), {255, 255, 255, 0}, {0, 0, 0, 0}).h;
                    crdInfo.str("");
                    crdInfo.clear();
                }
                // crdInfo << i
                //         << " x=" << snake.get_seg_pos(i).x
                //         << " y=" << snake.get_seg_pos(i).y;
                // ht = ht + newCanvas.render_text(0, ht, FONTNAME, 10, crdInfo.str(), {255, 255, 255, 0}, {0, 0, 0, 0}).h;
                crdInfo.str("");
                crdInfo.clear();
            }
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

#include <iostream>
#include <SDL2/SDL.h>

#include <random>
#include <cmath>
#include <sstream>
#include <iomanip>

#include "../include/canvas.hpp"
#include "../include/entity.hpp"
#include "../include/eHandler.hpp"

#define FONTNAME "/usr/share/fonts/TTF/RobotoMono-Regular.ttf"

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

        // State of coordinates fixation
        bool coordSet = 0;

        // Movement move;

        Entity snake = Entity();
        // snake.mov.direction = TO_RIGHT;
        // snake.mov.velocity = 1;

        // Start angle and end angle of mouth
        struct maDegree
        {
            int start;
            int end;
        } mouthAngle;

        // Mouth opening angle
        // int Angle = 0;

        // Segment radius
        int segRadius = 20;

        // Interval between a segmets
        int segInterval = segRadius * 1.5;

        // Main loop
        while (!quit)
        {
            Uint64 frameStart = SDL_GetTicks64();
            Uint64 frameCount;

            eHandler.poll_events(&e);
            eHandler.manage_entity(&snake);
            quit = eHandler.exit();

            // Polling events
            /* while (SDL_PollEvent(&e))
            {
                switch (e.type)
                {
                case SDL_QUIT:
                    quit = true;
                    break;

                // Keypressing handling
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_RIGHT:
                        // Check current direction and set new
                        if (mvDir != TO_LEFT && mvDir != TO_RIGHT)
                        {
                            mvDir == TO_UP ? trnDir = FROM_DOWN_TO_RIGHT : trnDir = FROM_UP_TO_RIGHT;
                            mvDir = TO_RIGHT;
                            // Reset coordinates fixation
                            coordSet = 0;
                        }
                        break;
                    case SDLK_LEFT:
                        // Check current direction and set new
                        if (mvDir != TO_RIGHT && mvDir != TO_LEFT)
                        {
                            mvDir == TO_UP ? trnDir = FROM_DOWN_TO_LEFT : trnDir = FROM_UP_TO_LEFT;
                            mvDir = TO_LEFT;
                            coordSet = 0;
                        }
                        break;
                    case SDLK_UP:
                        // Check current direction and set new
                        if (mvDir != TO_DOWN && mvDir != TO_UP)
                        {
                            mvDir == TO_LEFT ? trnDir = FROM_RIGHT_TO_UP : trnDir = FROM_LEFT_TO_UP;
                            mvDir = TO_UP;
                            coordSet = 0;
                        }
                        break;
                    case SDLK_DOWN:
                        // Check current direction and set new
                        if (mvDir != TO_UP && mvDir != TO_DOWN)
                        {
                            mvDir == TO_LEFT ? trnDir = FROM_RIGHT_TO_DOWN : trnDir = FROM_LEFT_TO_DOWN;
                            mvDir = TO_DOWN;
                            coordSet = 0;
                        }
                        break;
                    case SDLK_f:
                        newCanvas.toggle_fullscreen();
                        break;
                    case SDLK_r:
                        r = 255;
                        g = 0;
                        b = 0;
                        break;
                    case SDLK_g:
                        r = 0;
                        g = 255;
                        b = 0;
                        break;
                    case SDLK_b:
                        r = 0;
                        g = 0;
                        b = 255;
                        break;
                    case SDLK_F1:
                        newCanvas.clear();
                        break;
                    case SDLK_m:
                        ++dp;
                        // newCanvas.drawMandelbrot(1024, 768, 100);
                        break;
                    case SDLK_n:
                        --dp;
                        if (dp <= 0)
                        {
                            dp = 1;
                        }
                        break;
                    default:
                        break;
                    }

                default:
                    // std::cout << SDL_GetKeyName(e.key.keysym.sym) << "\n";
                    break;
                }
            } */

            SDL_GetWindowDisplayMode(newCanvas.get_window(), &dm);
            snake.detect_display_mode(&dm);

            /* switch (move.movD)
            {
            case TO_UP:
                // Fixes initial coordinates in turning
                if (!move.coordSet)
                {
                    fixedCrd.y = crd.y;
                    fixedCrd.x = crd.x;
                    move.coordSet = true;
                }
                // Evaluates turn direction
                switch (move.turnD)
                {
                case FROM_LEFT_TO_UP:
                    // Calculates turn animation
                    if (abs(fixedCrd.y - crd.y) < segInterval)
                    {
                        crd2.x = crd.x - sqrt(-pow(fixedCrd.y, 2) + 2 * crd.y * fixedCrd.y - pow(crd.y, 2) + pow(segInterval, 2));
                    }
                    else
                        crd2.x = fixedCrd.x;

                    if (crd2.x < fixedCrd.x)
                    {
                        crd2.y = fixedCrd.y;
                    }
                    else
                        crd2.y = crd.y + segInterval;

                    break;

                case FROM_RIGHT_TO_UP:
                    // Calculates turn animation
                    if (abs(fixedCrd.y - crd.y) < segInterval)
                    {
                        crd2.x = crd.x + sqrt(-pow(fixedCrd.y, 2) + 2 * crd.y * fixedCrd.y - pow(crd.y, 2) + pow(segInterval, 2));
                    }
                    else
                        crd2.x = fixedCrd.x;

                    if (crd2.x > fixedCrd.x)
                    {
                        crd2.y = fixedCrd.y;
                    }
                    else
                        crd2.y = crd.y + segInterval;

                    break;

                default:
                    crd2.x = crd.x;
                    crd2.y = crd.y + segInterval;
                    break;
                }
                // Movement animation
                crd.y -= dp;

                // Window bounds collision
                if (crd.y <= segRadius)
                {
                    crd.y = segRadius;
                }

                // Mouth bounds
                mouthAngle.start = 315;
                mouthAngle.end = 225;

                break;

            case TO_DOWN:
                // Fixes initial coordinates in turning
                if (!move.coordSet)
                {
                    fixedCrd.y = crd.y;
                    fixedCrd.x = crd.x;
                    move.coordSet = true;
                }

                switch (move.turnD)
                {
                case FROM_LEFT_TO_DOWN:
                    // Calculates turning animation
                    if (abs(fixedCrd.y - crd.y) < segInterval)
                    {
                        crd2.x = crd.x - sqrt(-pow(fixedCrd.y, 2) + 2 * crd.y * fixedCrd.y - pow(crd.y, 2) + pow(segInterval, 2));
                    }
                    else
                        crd2.x = fixedCrd.x;

                    if (crd2.x < fixedCrd.x)
                    {
                        crd2.y = fixedCrd.y;
                    }
                    else
                        crd2.y = crd.y - segInterval;
                    break;

                case FROM_RIGHT_TO_DOWN:
                    // Calculates turning animation
                    if (abs(fixedCrd.y - crd.y) < segInterval)
                    {
                        crd2.x = crd.x + sqrt(-pow(fixedCrd.y, 2) + 2 * crd.y * fixedCrd.y - pow(crd.y, 2) + pow(segInterval, 2));
                    }
                    else
                        crd2.x = fixedCrd.x;

                    if (crd2.x > fixedCrd.x)
                    {
                        crd2.y = fixedCrd.y;
                    }
                    else
                        crd2.y = crd.y - segInterval;
                    break;

                default:
                    crd2.x = crd.x;
                    crd2.y = crd.y - segInterval;
                    break;
                }

                // Movement animation
                crd.y += dp;

                // Window bounds collision
                if (crd.y >= dm.h - segRadius)
                {
                    crd.y = dm.h - segRadius;
                }

                // Mouth bounds
                mouthAngle.start = 135;
                mouthAngle.end = 45;

                break;

            case TO_LEFT:
                // Fixes initial coordinates in turning
                if (!move.coordSet)
                {
                    fixedCrd.y = crd.y;
                    fixedCrd.x = crd.x;
                    move.coordSet = true;
                }

                switch (move.turnD)
                {
                case FROM_UP_TO_LEFT:
                    // Calculates turning animation
                    if (abs(fixedCrd.x - crd.x) < segInterval)
                    {
                        crd2.y = crd.y - sqrt(-pow(fixedCrd.x, 2) + 2 * crd.x * fixedCrd.x - pow(crd.x, 2) + pow(segInterval, 2));
                    }
                    else
                        crd2.y = fixedCrd.y;

                    if (crd2.y < fixedCrd.y)
                    {
                        crd2.x = fixedCrd.x;
                    }
                    else
                        crd2.x = crd.x + segInterval;
                    break;

                case FROM_DOWN_TO_LEFT:
                    // Calculates turning animation
                    if (abs(fixedCrd.x - crd.x) < segInterval)
                    {
                        crd2.y = crd.y + sqrt(-pow(fixedCrd.x, 2) + 2 * crd.x * fixedCrd.x - pow(crd.x, 2) + pow(segInterval, 2));
                    }
                    else
                        crd2.y = fixedCrd.y;

                    if (crd2.y > fixedCrd.y)
                    {
                        crd2.x = fixedCrd.x;
                    }
                    else
                        crd2.x = crd.x + segInterval;
                    break;

                default:
                    crd2.x = crd.x + segInterval;
                    crd2.y = crd.y;
                    break;
                }

                // Movement animation
                crd.x -= dp;

                // Window bounds collision
                if (crd.x <= segRadius)
                {
                    crd.x = segRadius;
                }

                // Mouth bounds
                mouthAngle.start = 225;
                mouthAngle.end = 135;

                break;

            case TO_RIGHT:
                // Fixes initial coordinates in turning
                if (!move.coordSet)
                {
                    fixedCrd.y = crd.y;
                    fixedCrd.x = crd.x;
                    move.coordSet = true;
                }

                switch (move.turnD)
                {
                case FROM_UP_TO_RIGHT:
                    // Calculates turning animation
                    if (abs(fixedCrd.x - crd.x) < segInterval)
                    {
                        crd2.y = crd.y - sqrt(-pow(fixedCrd.x, 2) + 2 * crd.x * fixedCrd.x - pow(crd.x, 2) + pow(segInterval, 2));
                    }
                    else
                        crd2.y = fixedCrd.y;

                    if (crd2.y < fixedCrd.y)
                    {
                        crd2.x = fixedCrd.x;
                    }
                    else
                        crd2.x = crd.x - segInterval;
                    break;

                case FROM_DOWN_TO_RIGHT:
                    // Calculates turning animation
                    if (abs(fixedCrd.x - crd.x) < segInterval)
                    {
                        crd2.y = crd.y + sqrt(-pow(fixedCrd.x, 2) + 2 * crd.x * fixedCrd.x - pow(crd.x, 2) + pow(segInterval, 2));
                    }
                    else
                        crd2.y = fixedCrd.y;

                    if (crd2.y > fixedCrd.y)
                    {
                        crd2.x = fixedCrd.x;
                    }
                    else
                        crd2.x = crd.x - segInterval;
                    break;

                default:
                    crd2.x = crd.x - segInterval;
                    crd2.y = crd.y;
                    break;
                }

                // Movement animation
                crd.x += dp;

                // Window bounds collision
                if (crd.x >= dm.w - segRadius)
                {
                    crd.x = dm.w - segRadius;
                }

                // Mouth bounds
                mouthAngle.start = 45;
                mouthAngle.end = 315;

                break;

            default:
                break;
            }
 */

            newCanvas.set_color(r, g, b, 255);

            snake.calc_seg_position();

            newCanvas.render_entity(&snake, r, g, b, 255);

            // newCanvas.render_pie(snake.get_seg_pos(0), snake.get_radius(), snake.mouthCurrentAngle.start, snake.mouthCurrentAngle.end, r, g, b, 255);
            // for (size_t i = 1; i < snake.get_segs_num(); i++)
            // {
            //     newCanvas.render_circle(snake.get_seg_pos(i), snake.get_radius(), r, g, b, 255);
            // }

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

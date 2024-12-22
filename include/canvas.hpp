#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>

#include "entity.hpp"
#include "math.hpp"

class Canvas
{
public:
    Canvas(const char *windowName, int windowWidth, int windowHeight);
    ~Canvas();
    bool is_init();
    void redraw();
    SDL_Texture *loadTexture(const char *filename);
    void clear();
    void set_color(int r, int g, int b, int alpha);
    void render(Entity &);
    void render_pixel(Vect2f coord);
    void render_line(Vect2f startPoint, Vect2f endPoint);
    void render_rectangle(Vect2f crd, int w, int h);
    void render_circle(Vect2f crd, int rad, int r, int g, int b, int a);
    void render_pie(Vect2f crd, int rad, int start, int end, int r, int g, int b, int a);
    void render_rbox(Vect2f crd, int diag, int rad, int r, int g, int b, int a);
    void render_entity(Entity *ent, int r, int g, int b, int a);

    /// @brief Render text on created canvas
    /// @param x X coordinate
    /// @param y Y coordinate
    /// @param fontName Desired font name of the text
    /// @param fontSize Font size in pt
    /// @param text Text to render
    /// @param fgColor Foreground color
    /// @param bgColor Background color
    /// @return 
    SDL_Rect render_text(int x, int y, const char *fontName, int fontSize, std::string text, SDL_Color fgColor, SDL_Color bgColor);

    int getRefreshRate();
    Vect2f conv_crd(Vect2f);
    SDL_Window *get_window();
    SDL_Renderer *get_renderer();
    void toggle_fullscreen();
    void drawMandelbrot(int width, int height, int iter);

private:
    /// @brief The window to rendering
    SDL_Window *window;
    /// @brief Renderer
    SDL_Renderer *renderer;
    /// @brief Variable to show success initialize SDL
    bool SDLInitSuccess;
    int canvasHeight;
    int canvasWidth;
    int r;
    int g;
    int b;
    int alpha;
    Entity *entity;
};

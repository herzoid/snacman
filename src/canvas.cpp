#include "../include/canvas.hpp"

Canvas::Canvas(const char *windowName, int windowWidth, int windowHeight)
    : window(NULL), renderer(NULL), r(0), g(0), b(0), alpha(255)
{
    // SDL initialization
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDLInitSuccess = false;
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    }

    // TTF initialization
    if (TTF_Init() == -1)
    {
        SDLInitSuccess = false;
        std::cerr << "Не удалось инициализировать SDL_ttf: " << TTF_GetError() << std::endl;
        // SDL_Quit();
    }

    // Create window
    window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        SDLInitSuccess = false;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, /* SDL_RENDERER_SOFTWARE */ SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        SDLInitSuccess = false;
        std::cerr << "Не удалось создать рендерер: " << SDL_GetError() << std::endl;
        // SDL_Quit();
    }

    SDLInitSuccess = true;
    canvasWidth = windowWidth;
    canvasHeight = windowHeight;
}

Canvas::~Canvas()
{
    // SDL_FreeSurface(imageSurface);
    // imageSurface = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

bool Canvas::is_init()
{
    return SDLInitSuccess;
}

void Canvas::redraw()
{
    SDL_RenderPresent(renderer);
}

SDL_Texture *Canvas::loadTexture(const char *filename)
{
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        return nullptr;
    }
    else
    {
        SDL_Texture *texture = NULL;
        texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
        {
            return nullptr;
        }
        else
            return texture;
    }
}

void Canvas::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Canvas::set_color(int r, int g, int b, int alpha)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, alpha);
}

void Canvas::render(Entity &pEntity)
{
    SDL_Rect src;
    src.x = pEntity.getCurFrame().x;
    src.y = pEntity.getCurFrame().y;
    src.w = pEntity.getCurFrame().w;
    src.h = pEntity.getCurFrame().h;
    SDL_Rect dst;
    dst.x = pEntity.get_pos().x;
    dst.y = pEntity.get_pos().y;
    dst.w = pEntity.getCurFrame().w;
    dst.h = pEntity.getCurFrame().h;

    SDL_RenderCopy(renderer, pEntity.get_texture(), &src, &dst);
}

void Canvas::render_pixel(Vect2f coord)
{
    // SDL_SetRenderDrawColor(renderer, RGBA.r, RGBA.g, b, alpha);
    SDL_RenderDrawPointF(renderer, coord.x, coord.y);
}

void Canvas::render_line(Vect2f startPoint, Vect2f endPoint)
{
    SDL_RenderDrawLineF(renderer, startPoint.x, startPoint.y, endPoint.x, endPoint.y);
}

void Canvas::render_rectangle(Vect2f crd, int w, int h)
{
    SDL_Rect rct;
    rct.x = crd.x;
    rct.y = crd.y;
    rct.w = w;
    rct.h = h;
    SDL_RenderDrawRect(renderer, &rct);
}

void Canvas::render_circle(Vect2f crd, int rad, int r, int g, int b, int a)
{

    filledCircleRGBA(renderer, crd.x, crd.y, rad, r, g, b, a);
}

void Canvas::render_pie(Vect2f crd, int rad, int start, int end, int r, int g, int b, int a)
{
    filledPieRGBA(renderer, crd.x, crd.y, rad, start, end, r, g, b, a);
}

void Canvas::render_entity(Entity ent)
{
}

SDL_Rect Canvas::render_text(int x, int y, const char *fontName, int fontSize, std::string text, SDL_Color fgColor, SDL_Color bgColor)
{
    // Загрузка шрифта
    TTF_Font *font = TTF_OpenFont(fontName, fontSize);
    if (!font)
    {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
    }
    // Рендеринг текста
    SDL_Surface *textSurface = TTF_RenderUTF8_LCD(font, text.c_str(), fgColor, bgColor);
    if (!textSurface)
    {
        std::cerr << "Unable to render text surface! TTF_Error: " << TTF_GetError() << std::endl;
    }
    TTF_CloseFont(font);

    // Создание текстовой текстуры
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface); // Освобождаем поверхность после создания текстуры

    // // Получение размеров текстуры
    // int textWidth, textHeight;
    // SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

    // Рендеринг текстуры
    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
    return renderQuad;
}

int Canvas::getRefreshRate()
{
    int displayIndex = SDL_GetWindowDisplayIndex(window);
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(displayIndex, 0, &mode);
    return mode.refresh_rate;
}

Vect2f Canvas::conv_crd(Vect2f coord)
{
    Vect2f retv;
    retv.x = coord.x + canvasWidth / 2;
    retv.y = canvasHeight / 2 - coord.y;
    return retv;
}

SDL_Window *Canvas::get_window()
{
    return window;
}

SDL_Renderer *Canvas::get_renderer()
{
    return renderer;
}

void Canvas::toggle_fullscreen()
{
    Uint32 fullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP; // or SDL_WINDOW_FULLSCREEN
    bool isFullscreen = (SDL_GetWindowFlags(window) & fullscreenFlag) != 0;
    SDL_SetWindowFullscreen(window, isFullscreen ? 0 : fullscreenFlag);
}

void Canvas::drawMandelbrot(int width, int height, int iter)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            double real = (x - width / 2.0) * 4.0 / width;   // Масштабирование по оси X
            double imag = (y - height / 2.0) * 4.0 / height; // Масштабирование по оси Y
            std::complex<double> c(real, imag);
            int n = mandelbrot(c, iter);
            // Цвет в зависимости от количества итераций
            int color = (n == iter) ? 0 : (255 * n / iter);
            SDL_SetRenderDrawColor(renderer, color, color, color, 255);
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

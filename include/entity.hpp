#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <tuple>

#include "math.hpp"
// #include "utils.hpp"

// Movement directions
typedef enum
{
    TO_LEFT = 0b0110,
    TO_RIGHT = 0b1001,
    TO_DOWN = 0b0111,
    TO_UP = 0b1000,
} movementDirection;

// Turning directions type
typedef enum
{
    FROM_UP_TO_LEFT,
    FROM_UP_TO_RIGHT,
    FROM_DOWN_TO_LEFT,
    FROM_DOWN_TO_RIGHT,
    FROM_LEFT_TO_UP,
    FROM_LEFT_TO_DOWN,
    FROM_RIGHT_TO_UP,
    FROM_RIGHT_TO_DOWN
} turnDirection;

class Entity
{
private:
    /// @brief Initial coordinates of the first segment
    Vect2f position;

    /// @brief Radius if the segment
    int segRadius;

    /// @brief Interval between segments
    int segInterval;

    /// @brief The angle of the mouth
    int mouthAngle;

    /// @brief
    int incAngle;

    /// @brief Pointer to struct SDL_DisplayMode
    SDL_DisplayMode *dmode;

    /// @brief Structure type that represents start and end angles of the mouth in the first segment of snake
    typedef struct
    {
        /// @brief Start angle of the mouth
        int start;
        /// @brief End angle of the mouth
        int end;
    } mouthStruct;

    /// @brief Represents bounds of the mouth
    mouthStruct mouthBounds;

    /// @brief Number of segments
    int segNum;

    /// @brief Coordinates of every body segment's of snake
    std::vector<Vect2f> segsPos;

    /// @brief Stores the coordinates of the turns
    std::vector<std::tuple<Vect2f, turnDirection, int>> turnsPos;

    /// @brief Calculates current angle of the mouth
    void calc_mouth_angle();

public:
    /// @brief The structure that defines movement
    struct MovementStruct
    {
        movementDirection direction;
        turnDirection turn;
        int velocity;
        bool coordSet;
        MovementStruct();
    };

    MovementStruct mov;

    Entity();
    Vect2f &get_seg_pos(int segNumber);
    auto &get_turn_pos(int number);
    int get_segs_num();
    int get_radius();
    int get_seg_interval();
    SDL_Texture *get_texture();
    SDL_Rect getCurFrame();
    void detect_display_mode(SDL_DisplayMode *dm);

    /// @brief Calculates coordinates of every body segment's center
    void calc_seg_position();

    /// @brief Current angle of the mouth
    mouthStruct mouthCurrentAngle;

    void add_segment();
};

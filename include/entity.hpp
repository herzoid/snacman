#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <tuple>
#include <utility>

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
    FROM_UP_TO_LEFT = 103,
    FROM_UP_TO_RIGHT = 151,
    FROM_DOWN_TO_LEFT = 104,
    FROM_DOWN_TO_RIGHT = 152,
    FROM_LEFT_TO_UP = 137,
    FROM_LEFT_TO_DOWN = 121,
    FROM_RIGHT_TO_UP = 134,
    FROM_RIGHT_TO_DOWN = 118
} turnDirection;

class Entity
{
private:
    /// @brief Initial coordinates of the first segment
    Vect2f position;

    /// @brief Radius if the segment
    double segRadius;

    /// @brief Interval between segments
    double segInterval;

    /// @brief The angle of the mouth
    int mouthAngle;

    /// @brief
    int incAngle;

    double flexRatio;

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

    /// @brief Number of the segments
    int segNum;

    /// @brief Coordinates of every body segment's of snake
    // std::vector<Vect2f> segsPos;
    std::vector<std::pair<Vect2f, movementDirection>> segsPos;

    /// @brief Stores the coordinates of the turns
    std::vector<std::tuple<Vect2f, turnDirection, int>> turnsPos;

    /// @brief Calculates current angle of the mouth
    void calc_mouth_angle();

    /// @brief Returns turn data
    /// @return Coordinates or turn direction or segments number
    auto get_turn_data(std::tuple<Vect2f, turnDirection, int> &t, int item);

public:
    /// @brief The structure that defines movement
    struct MovementStruct
    {
        movementDirection direction;
        turnDirection turn;
        int velocity;
        bool coordSet;
        /// @brief MovementSruct constructor
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

    /// @brief Sets the head segment movement direction
    void set_head_direction(movementDirection mD);

    /// @brief Makes the entity to move
    void move_entity();

    /// @brief Gets the head segment movement direction
    movementDirection &get_seg_dir(int segNumber);

    void set_seg_pos(int segNumber);

    void set_head_dir(int segNumber);

    /// @brief Calculates coordinates of every body segment's center
    void calc_seg_position();

    void calc_segment_pos();

    /// @brief Current angle of the mouth
    mouthStruct mouthCurrentAngle;

    /// @brief Sets turn coordinates
    void fix_turn_data();

    /// @brief Gets flexion ratio of the entity
    double get_flexRatio();

    /// @brief Adds a segment to entity
    void add_segment();

    void drop_feed();
};

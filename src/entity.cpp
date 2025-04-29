#include "../include/entity.hpp"
#include "entity.hpp"

void Entity::calc_mouth_angle()
{
    // Mouth animation
    if (mouthAngle == 0)
    {
        incAngle = 4;
    };
    if (mouthAngle > 42)
    {
        incAngle *= -1;
    };
    mouthAngle = mouthAngle + incAngle;
    mouthCurrentAngle.start = mouthBounds.start - mouthAngle;
    mouthCurrentAngle.end = mouthBounds.end + mouthAngle;
}

void Entity::grow_up()
{
    add_segment();
    // segRadius++;
    // segInterval = segRadius * intervalRatio;
}

void Entity::fix_turn_data()
{
    // if (!mov.coordSet)
    // {
    turnsPos.emplace_back(std::make_tuple(get_seg_pos(0), mov.turn, 0));
    mov.coordSet = true;
    // }
}

// template <std::size_t... Is>
// auto get_element(const std::tuple<Vect2f, turnDirection, int> &t, int index, std::index_sequence<Is...>)
// {
//     return (index == Is ? std::get<Is>(t) : ...);
// }

// auto Entity::get_turn_data(std::tuple<Vect2f, turnDirection, int> &t, int item)
// {
//     return get_element(t, item, std::make_index_sequence<3>{});
// }

Entity::Entity()
    : segNum(10),
      position(200, 600),
      segRadius(10),
      segInterval(segRadius * intervalRatio),
      mouthAngle(0),
      flexRatio(1),
      foodIsDropped(false)

{
    for (size_t i = 0; i < segNum; i++)
    {
        if (i == 0)
            segsPos.emplace_back(std::make_pair(position, TO_RIGHT));
        else
        {
            position.x -= segInterval;
            // position.y = 200;
            segsPos.emplace_back(std::make_pair(position, get_seg_dir(0)));
        }
    }
    // Defines mouth bounds
    mouthBounds.start = 45;
    mouthBounds.end = 315;
}

Vect2f &Entity::get_seg_pos(int segNumber)
{
    return std::get<0>(segsPos.at(segNumber));
}

Vect2f &Entity::get_turn_pos(int number)
{
    return std::get<0>(turnsPos.at(turnsPos.size() - 1));
}

bool Entity::check_turns()
{
    return !turnsPos.size() ? false : true;
    // if (turnsPos.size() !=)
    // {
    //     /* code */
    // }

    // return false;
}

int Entity::last_turn()
{
    return (turnsPos.size() - 1);
}

int Entity::get_segs_num()
{
    return segsPos.size();
}

int Entity::get_radius()
{
    return segRadius;
}

double Entity::get_seg_interval()
{
    return segInterval;
}

void Entity::detect_display_mode(SDL_DisplayMode *dm)
{
    dmode = dm;
}

void Entity::set_head_direction(movementDirection mD)
{
    segsPos.at(0).second = mD;
}

movementDirection &Entity::get_seg_dir(int segNumber)
{
    return std::get<1>(segsPos.at(segNumber));
}

void Entity::move_entity()
{
    switch (get_seg_dir(0))
    {
    case TO_UP:
        // Defines mouth bounds
        mouthBounds.start = 315;
        mouthBounds.end = 225;

        // Movement animation
        std::get<0>(segsPos.at(0)).y -= mov.velocity;

        // Window bounds collision
        if (std::get<0>(segsPos.at(0)).y <= segRadius)
        {
            std::get<0>(segsPos.at(0)).y = segRadius;
        }
        break;

    case TO_RIGHT:
        // Defines mouth bounds
        mouthBounds.start = 45;
        mouthBounds.end = 315;

        // Movement animation
        std::get<0>(segsPos.at(0)).x += mov.velocity;

        // Window bounds collision
        if (std::get<0>(segsPos.at(0)).x >= dmode->w - segRadius)
        {
            std::get<0>(segsPos.at(0)).x = dmode->w - segRadius;
        }
        break;

    case TO_DOWN:
        // Define mouth bounds
        mouthBounds.start = 135;
        mouthBounds.end = 45;

        // Movement animation
        std::get<0>(segsPos.at(0)).y += mov.velocity;

        // Window bounds collision
        if (std::get<0>(segsPos.at(0)).y >= dmode->h - segRadius)
        {
            std::get<0>(segsPos.at(0)).y = dmode->h - segRadius;
        }
        break;

    case TO_LEFT:
        // Define mouth bounds
        mouthBounds.start = 225;
        mouthBounds.end = 135;

        // Movement animation
        std::get<0>(segsPos.at(0)).x -= mov.velocity;

        // Window bounds collision
        if (std::get<0>(segsPos.at(0)).x <= segRadius)
        {
            std::get<0>(segsPos.at(0)).x = segRadius;
        }
        break;

    default:
        break;
    }

    body_collision();

    calc_mouth_angle();
}

void Entity::set_seg_pos(int segNumber)
{
    // segsPos.at(segNumber).first = 0;
}

void Entity::calc_segment_pos()
{

    int segCnt = segNum;
    int k;

    for (size_t i = 1; i < segNum; i++)
    {
        // Previous segment coordinates
        Vect2f crd = std::get<0>(segsPos.at(i - 1));
        // Next segment coordinates
        Vect2f crd2 = std::get<0>(segsPos.at(i));
        // Previous segment movement direction
        movementDirection &dirPrev = segsPos.at(i - 1).second;
        // Next segment movement direction
        movementDirection &dirNext = segsPos.at(i).second;
        // Turn coordinates
        Vect2f fixedCrd;
        // Turn direction
        turnDirection turnDir;
        int result = (dirPrev << 4) + dirNext;

        switch (result)
        {
        case (TO_UP << 4) + TO_UP:
            crd2.x = crd.x;
            crd2.y = crd.y + segInterval;
            dirNext = TO_UP;
            break;
        case (TO_RIGHT << 4) + TO_RIGHT:
            crd2.x = crd.x - segInterval;
            crd2.y = crd.y;
            dirNext = TO_RIGHT;
            break;
        case (TO_DOWN << 4) + TO_DOWN:
            crd2.x = crd.x;
            crd2.y = crd.y - segInterval;
            dirNext = TO_DOWN;
            break;
        case (TO_LEFT << 4) + TO_LEFT:
            crd2.x = crd.x + segInterval;
            crd2.y = crd.y;
            dirNext = TO_LEFT;
            break;

        case FROM_LEFT_TO_UP:
            for (auto it = turnsPos.rbegin(); it != turnsPos.rend(); ++it)
            {
                if (std::get<1>(*it) == result && std::get<0>(*it).y == crd2.y)
                {
                    fixedCrd = std::get<0>(*it);
                    if (abs(fixedCrd.y - crd.y) <= segInterval)
                    {
                        crd2.x = crd.x - sqrt(-pow(fixedCrd.y, 2) + 2 * crd.y * fixedCrd.y - pow(crd.y, 2) + pow(segInterval, 2));
                    }
                    else
                    {
                        crd2.x == fixedCrd.x;
                        dirNext = TO_UP;
                        std::get<2>(*it)++;
                    }
                }
            }
            break;

        case FROM_RIGHT_TO_UP:
            for (auto it = turnsPos.rbegin(); it != turnsPos.rend(); ++it)
            {
                if (std::get<1>(*it) == result && std::get<0>(*it).y == crd2.y)
                {
                    fixedCrd = std::get<0>(*it);
                    if (abs(fixedCrd.y - crd.y) <= segInterval)
                    {
                        crd2.x = crd.x + sqrt(-pow(fixedCrd.y, 2) + 2 * crd.y * fixedCrd.y - pow(crd.y, 2) + pow(segInterval, 2));
                    }
                    else
                    {
                        crd2.x == fixedCrd.x;
                        dirNext = TO_UP;
                        std::get<2>(*it)++;
                    }
                }
            }
            break;

        case FROM_LEFT_TO_DOWN:
            for (auto it = turnsPos.rbegin(); it != turnsPos.rend(); ++it)
            {
                if (std::get<1>(*it) == result && std::get<0>(*it).y == crd2.y)
                {
                    fixedCrd = std::get<0>(*it);
                    if (abs(fixedCrd.y - crd.y) <= segInterval)
                    {
                        crd2.x = crd.x - sqrt(-pow(fixedCrd.y, 2) + 2 * crd.y * fixedCrd.y - pow(crd.y, 2) + pow(segInterval, 2));
                    }
                    else
                    {
                        crd2.x == fixedCrd.x;
                        dirNext = TO_DOWN;
                        std::get<2>(*it)++;
                    }
                }
            }
            break;

        case FROM_RIGHT_TO_DOWN:
            for (auto it = turnsPos.rbegin(); it != turnsPos.rend(); ++it)
            {
                if (std::get<1>(*it) == result && std::get<0>(*it).y == crd2.y)
                {
                    fixedCrd = std::get<0>(*it);
                    if (abs(fixedCrd.y - crd.y) <= segInterval)
                    {
                        crd2.x = crd.x + sqrt(-pow(fixedCrd.y, 2) + 2 * crd.y * fixedCrd.y - pow(crd.y, 2) + pow(segInterval, 2));
                    }
                    else
                    {
                        crd2.x == fixedCrd.x;
                        dirNext = TO_DOWN;
                        std::get<2>(*it)++;
                    }
                }
            }
            break;

        case FROM_UP_TO_RIGHT:
            for (auto it = turnsPos.rbegin(); it != turnsPos.rend(); ++it)
            {
                if (std::get<1>(*it) == result && std::get<0>(*it).x == crd2.x)
                {
                    fixedCrd = std::get<0>(*it);
                    if (abs(fixedCrd.x - crd.x) <= segInterval)
                    {
                        crd2.y = crd.y - sqrt(-pow(fixedCrd.x, 2) + 2 * crd.x * fixedCrd.x - pow(crd.x, 2) + pow(segInterval, 2));
                    }
                    else
                    {
                        crd2.y == fixedCrd.y;
                        dirNext = TO_RIGHT;
                        std::get<2>(*it)++;
                    }
                }
            }
            break;

        case FROM_UP_TO_LEFT:
            for (auto it = turnsPos.rbegin(); it != turnsPos.rend(); ++it)
            {
                if (std::get<1>(*it) == result && std::get<0>(*it).x == crd2.x)
                {
                    fixedCrd = std::get<0>(*it);
                    if (abs(fixedCrd.x - crd.x) <= segInterval)
                    {
                        crd2.y = crd.y - sqrt(-pow(fixedCrd.x, 2) + 2 * crd.x * fixedCrd.x - pow(crd.x, 2) + pow(segInterval, 2));
                    }
                    else
                    {
                        crd2.y == fixedCrd.y;
                        dirNext = TO_LEFT;
                        std::get<2>(*it)++;
                    }
                }
            }
            break;

        case FROM_DOWN_TO_RIGHT:
            for (auto it = turnsPos.rbegin(); it != turnsPos.rend(); ++it)
            {
                if (std::get<1>(*it) == result && std::get<0>(*it).x == crd2.x)
                {
                    fixedCrd = std::get<0>(*it);
                    if (abs(fixedCrd.x - crd.x) <= segInterval)
                    {
                        crd2.y = crd.y + sqrt(-pow(fixedCrd.x, 2) + 2 * crd.x * fixedCrd.x - pow(crd.x, 2) + pow(segInterval, 2));
                    }
                    else
                    {
                        crd2.y == fixedCrd.y;
                        dirNext = TO_RIGHT;
                        std::get<2>(*it)++;
                    }
                }
            }
            break;

        case FROM_DOWN_TO_LEFT:
            for (auto it = turnsPos.rbegin(); it != turnsPos.rend(); ++it)
            {
                if (std::get<1>(*it) == result && std::get<0>(*it).x == crd2.x)
                {
                    fixedCrd = std::get<0>(*it);
                    if (abs(fixedCrd.x - crd.x) <= segInterval)
                    {
                        crd2.y = crd.y + sqrt(-pow(fixedCrd.x, 2) + 2 * crd.x * fixedCrd.x - pow(crd.x, 2) + pow(segInterval, 2));
                    }
                    else
                    {
                        crd2.y == fixedCrd.y;
                        dirNext = TO_LEFT;
                        std::get<2>(*it)++;
                    }
                }
            }
            break;

        default:
            break;
        }
        // Checks for all tail segments that they was passed a turn
        for (auto it = turnsPos.rbegin(); it != turnsPos.rend(); ++it)
        {
            if (std::get<2>(*it) == segNum - 1)
            {
                turnsPos.erase(turnsPos.begin());
            }
        }
        segsPos.at(i).first = crd2;
        // }
    }
    move_entity();
}

double Entity::get_flexRatio()
{
    return flexRatio;
}

Vect2f Entity::get_food_pos()
{
    return foodPos;
}

void Entity::add_segment()
{
    movementDirection moveDir = segsPos.at(segNum - 1).second;
    switch (moveDir)
    {
    case TO_RIGHT:
        position.x = std::get<0>(segsPos.at(segNum - 1)).x - segInterval;
        position.y = std::get<0>(segsPos.at(segNum - 1)).y;
        break;

    case TO_LEFT:
        position.x = std::get<0>(segsPos.at(segNum - 1)).x + segInterval;
        position.y = std::get<0>(segsPos.at(segNum - 1)).y;
        break;

    case TO_UP:
        position.x = std::get<0>(segsPos.at(segNum - 1)).x;
        position.y = std::get<0>(segsPos.at(segNum - 1)).y + segInterval;
        break;

    case TO_DOWN:
        position.x = std::get<0>(segsPos.at(segNum - 1)).x;
        position.y = std::get<0>(segsPos.at(segNum - 1)).y - segInterval;
        break;

    default:
        break;
    }
    segsPos.emplace_back(std::make_pair(position, moveDir));
    segNum = segsPos.size();
}

void Entity::generate_food_position()
{
    if (!foodIsDropped)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        int min = segInterval;
        int maxX = dmode->w - segInterval;
        int maxY = dmode->h - segInterval;
        std::uniform_int_distribution distrX(min, maxX);
        std::uniform_int_distribution distrY(min, maxY);
        foodPos = Vect2f(distrX(gen), distrY(gen));
        foodIsDropped = true;
    }
}

bool Entity::grab_the_food(sound &sndObj)
{
    int grabRadius = segRadius / grabRatio;
    if (abs(foodPos.x - get_seg_pos(0).x) <= grabRadius && abs(foodPos.y - get_seg_pos(0).y) <= grabRadius)
    {
        foodIsDropped = false;
        grow_up();
        return true;
    }
    else
        return false;
}

void Entity::detect_the_food()
{
    int deltaX, deltaY;
    deltaX = get_seg_pos(0).x - foodPos.x;
    deltaY = get_seg_pos(0).y - foodPos.y;
}

void Entity::body_collision()
{
    bool checkXDistance;
    bool checkYDistance;
    for (size_t i = 5; i < segNum; i++)
    {
        switch (get_seg_dir(0))
        {
        case TO_UP:

            checkXDistance = abs(get_seg_pos(0).x - get_seg_pos(i).x) <= 2 * segRadius;
            checkYDistance = get_seg_pos(0).y > get_seg_pos(i).y && (abs(get_seg_pos(0).y - get_seg_pos(i).y) <= 2 * segRadius);
            if (checkXDistance && checkYDistance)
            {
                std::get<0>(segsPos.at(0)).y = get_seg_pos(i).y + 2 * segRadius;
            }
            break;
        case TO_DOWN:
            checkXDistance = abs(get_seg_pos(0).x - get_seg_pos(i).x) <= 2 * segRadius;
            checkYDistance = get_seg_pos(0).y < get_seg_pos(i).y && (abs(get_seg_pos(0).y - get_seg_pos(i).y) <= 2 * segRadius);
            if (checkXDistance && checkYDistance)
            {
                std::get<0>(segsPos.at(0)).y = get_seg_pos(i).y - 2 * segRadius;
            }
            break;
        case TO_RIGHT:
            checkYDistance = abs(get_seg_pos(0).y - get_seg_pos(i).y) <= 2 * segRadius;
            checkXDistance = get_seg_pos(0).x < get_seg_pos(i).x && (abs(get_seg_pos(0).x - get_seg_pos(i).x) <= 2 * segRadius);
            if (checkXDistance && checkYDistance)
            {
                std::get<0>(segsPos.at(0)).x = get_seg_pos(i).x - 2 * segRadius;
            }
            break;
        case TO_LEFT:
            checkYDistance = abs(get_seg_pos(0).y - get_seg_pos(i).y) <= 2 * segRadius;
            checkXDistance = get_seg_pos(0).x > get_seg_pos(i).x && (abs(get_seg_pos(0).x - get_seg_pos(i).x) <= 2 * segRadius);
            if (checkXDistance && checkYDistance)
            {
                std::get<0>(segsPos.at(0)).x = get_seg_pos(i).x + 2 * segRadius;
            }
            break;

        default:
            break;
        }
    }
}

Entity::MovementStruct::MovementStruct() : direction(TO_RIGHT), velocity(3)
{
}

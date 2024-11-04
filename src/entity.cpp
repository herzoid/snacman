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

Entity::Entity()
    : segNum(4),
      position(200, 200),
      segRadius(20),
      segInterval(segRadius * 1.5),
      mouthAngle(0)

{
    for (size_t i = 0; i < segNum; i++)
    {
        if (i == 0)
            segsPos.emplace_back(position);
        else
            segsPos.emplace_back(0, 0);
    }
}

Vect2f &Entity::get_seg_pos(int segNumber)
{
    return segsPos.at(segNumber);
}

auto &Entity::get_turn_pos(int number)
{
    for (auto &&i : turnsPos)
    {
        Vect2f crd;
        turnDirection td;
        int cnt;
        std::tie(crd, td, cnt) = i;
    }

    return std::get<0>(turnsPos.at(number));
}

int Entity::get_segs_num()
{
    return segsPos.size();
}

int Entity::get_radius()
{
    return segRadius;
}

int Entity::get_seg_interval()
{
    return segRadius * 1.5;
}

void Entity::detect_display_mode(SDL_DisplayMode *dm)
{
    dmode = dm;
}

void Entity::calc_seg_position()
{
    switch (mov.direction)
    {
    case TO_RIGHT:
        // Fixes initial coordinates in turning
        if (!mov.coordSet)
        {
            turnsPos.emplace_back(std::make_tuple(get_seg_pos(0), mov.turn, segNum));
            mov.coordSet = true;
        }

        // Movement animation
        segsPos.at(0).x += mov.velocity;
        for (size_t i = 1; i < segNum; i++)
        {
            segsPos.at(i).x = segsPos.at(i - 1).x - segInterval;
            segsPos.at(i).y = segsPos.at(i - 1).y;
        }

        // Window bounds collision
        if (segsPos.at(0).x >= dmode->w - segRadius)
        {
            segsPos.at(0).x = dmode->w - segRadius;
        }

        // Evaluates mouth bounds
        mouthBounds.start = 45;
        mouthBounds.end = 315;
        break;
    default:
        break;
    }
    calc_mouth_angle();
}

void Entity::add_segment()
{
    switch (mov.direction)
    {
    case TO_RIGHT:
        position.x = segsPos.at(segNum - 1).x + segInterval;
        position.y = segsPos.at(segNum - 1).y;
        segsPos.emplace_back(position);
        segNum = segsPos.size();
        break;

    default:
        break;
    }
}

Entity::MovementStruct::MovementStruct() : direction(TO_RIGHT), velocity(1)
{
}

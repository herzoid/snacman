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

void Entity::fix_turn_data()
{
    if (!mov.coordSet)
    {
        turnsPos.emplace_back(std::make_tuple(get_seg_pos(0), mov.turn, segNum));
        mov.coordSet = true;
    }
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
    Vect2f crd, crd2, fixedCrd;
    int segCnt = segNum;

    switch (mov.direction)
    {

    case TO_UP:
        // Fixes initial coordinates in turning
        // fix_turn_data();

        for (size_t i = 1; i < segNum; i++)
        {

            crd = segsPos.at(i - 1);
            crd2 = segsPos.at(i);
            fixedCrd = std::get<0>(turnsPos.at(0));
            turnDirection turn = std::get<1>(turnsPos.at(0));

            // Evaluates turn direction
            switch (turn)
            {
            case FROM_LEFT_TO_UP:
                // Calculates turn animation
                if (abs(fixedCrd.y - crd.y) < segInterval)
                {
                    crd2.x = crd.x - sqrt(-pow(fixedCrd.y, 2) + 2 * crd.y * fixedCrd.y - pow(crd.y, 2) + pow(segInterval, 2));
                }
                else
                {
                    crd2.x = fixedCrd.x;
                    segCnt--;
                }

                if (crd2.x < fixedCrd.x)
                {
                    crd2.y = fixedCrd.y;
                }
                else
                    crd2.y = crd.y + segInterval;
                // segsPos.at(i) = crd2;

                break;

            case FROM_RIGHT_TO_UP:
                // Calculates turn animation
                if (abs(fixedCrd.y - crd.y) < segInterval)
                {
                    crd2.x = crd.x + sqrt(-pow(fixedCrd.y, 2) + 2 * crd.y * fixedCrd.y - pow(crd.y, 2) + pow(segInterval, 2));
                }
                else
                {
                    crd2.x = fixedCrd.x;
                    segCnt--;
                }

                if (crd2.x > fixedCrd.x)
                {
                    crd2.y = fixedCrd.y;
                }
                else
                    crd2.y = crd.y + segInterval;
                // segsPos.at(i) = crd2;
                break;

            default:
                crd2.x = crd.x;
                crd2.y = crd.y + segInterval;
                // segsPos.at(i) = crd2;
                break;
            }
            segsPos.at(i) = crd2;
        }

        // Movement animation
        segsPos.at(0).y -= mov.velocity;

        // Defines mouth bounds
        mouthBounds.start = 315;
        mouthBounds.end = 225;

        // Window bounds collision
        if (segsPos.at(0).y <= segRadius)
        {
            segsPos.at(0).y = segRadius;
        }

        break;

    case TO_RIGHT:
        // Fixes initial coordinates in turning
        // fix_turn_data();

        if (turnsPos.size() != 0)
        {
            fixedCrd = std::get<0>(turnsPos.at(0));
        }

        for (size_t i = 1; i < segNum; i++)
        {
            // Vect2f crd, crd2, fixedCrd;
            crd = segsPos.at(i - 1);
            crd2 = segsPos.at(i);

            switch (mov.turn)
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
            segsPos.at(i) = crd2;
        }

        // Movement animation
        segsPos.at(0).x += mov.velocity;

        // Defines mouth bounds
        mouthBounds.start = 45;
        mouthBounds.end = 315;

        // Window bounds collision
        if (segsPos.at(0).x >= dmode->w - segRadius)
        {
            segsPos.at(0).x = dmode->w - segRadius;
        }

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

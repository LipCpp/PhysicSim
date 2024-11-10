#ifndef PHYSICSSIM_CIRCLE_H
#define PHYSICSSIM_CIRCLE_H

#include "constants.h"

struct Circle
{
    Circle() = default;
    Circle(Vector2 pos, float radius, Vector2 velocity, uint index, Color color);
    ~Circle();
    float radius;
    Vector2 pos;
    Vector2 velocity;
    Color color;
    uint index;
    uint row;
    uint col;
    Vector2 getPos();
    void setPos(Vector2 newPos);
    Vector2 getDir();
};


#endif //PHYSICSSIM_CIRCLE_H

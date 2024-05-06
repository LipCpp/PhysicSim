#ifndef PHYSICSSIM_CIRCLE_H
#define PHYSICSSIM_CIRCLE_H

#include "constants.h"


class Circle
{
public:
    Circle();
    Circle(float x, float y, float radius, Vector2 dir, uint index, const Color &color);
    ~Circle();
public:
    float x;
    float y;
    float radius;
    Vector2 direction;
    Color color;
    uint index;
    uint row;
    uint col;
    Vector2 getPos();
    Vector2 getDir();
};


#endif //PHYSICSSIM_CIRCLE_H

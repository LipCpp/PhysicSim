#include "Circle.h"


/*
 * Constructors and destr.
 */
Circle::Circle() {}

Circle::Circle(float x, float y, float radius, Vector2 dir, uint index, const Color &color) :
    x(x),
    y(y),
    radius(radius),
    direction(dir),
    index(index),
    color(color)
{}

Circle::~Circle() { }


/*
 * Class methods
 */
Vector2 Circle::getPos() { return (Vector2) { x, y }; }

Vector2 Circle::getDir() { return direction; }

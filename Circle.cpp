#include "Circle.h"


/*
 * Constructors and destr.
 */

Circle::Circle(Vector2 pos, float radius, Vector2 velocity, uint index, Color color) :
    pos(pos),
    radius(radius),
    velocity(velocity),
    index(index),
    color(color)
{}

Circle::~Circle() { }


/*
 * Class methods
 */
Vector2 Circle::getPos() { return pos; }

void Circle::setPos(Vector2 newPos) { pos = newPos; }

Vector2 Circle::getDir() { return velocity; }

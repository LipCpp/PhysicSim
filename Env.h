#ifndef PHYSICSSIM_ENV_H
#define PHYSICSSIM_ENV_H

#include "constants.h"
#include "FixedGrid.h"
#include "Circle.h"


class Env
{
public:
    Env();
    ~Env();
private:
    void updateDirection();     // move obj by direction vector
    void updateGridMatrix();    // updates grid: list<uint> in FixedGrid
    void checkForColl();        // check if circle collides with circles located in one of the 8 surrounding circles
    void checkSurr(uint currIndex);
    void drawCircles();         // spawn circles at random pos
    FixedGrid fixedGrid;
    vector<Circle> obj;
    void initRandomObj(const uint numObj);
};

#endif //PHYSICSSIM_ENV_H

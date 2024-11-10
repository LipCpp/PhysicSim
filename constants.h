#ifndef PHYSICSSIM_CONSTANTS_H
#define PHYSICSSIM_CONSTANTS_H

#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

using namespace std;
typedef unsigned int uint;

#define DEBUG 1         // when enabled: prints useful debugging information
#define WIDTH 700
#define HEIGHT 500
#define TITLE "Physics Simulation (v 0.1.0)"
#define FPS 1
#define NUM_CIRCLES 20   // for debug opt.: 10
#define GRID_ROWS 10     // debug: 5
#define GRID_COLS 10    // debug: 10
const uint RAD_CIRCLE = 20;
const uint DIA_CIRCLE = 2 * RAD_CIRCLE;
const uint GRID_WIDTH = GRID_COLS * DIA_CIRCLE;
const uint GRID_HEIGHT = GRID_ROWS * DIA_CIRCLE;


#endif //PHYSICSSIM_CONSTANTS_H

#ifndef PHYSICSSIM_FIXEDGRID_H
#define PHYSICSSIM_FIXEDGRID_H

#include <vector>
#include <list>
#include "constants.h"


class FixedGrid
{
public:
    FixedGrid();
    ~FixedGrid();
public:
    void drawGridCells();
    const uint getOffsetX() const;
    const uint getOffsetY() const;
    vector<vector<Rectangle>>* getCellMatrix();
    vector<vector<vector<uint>>>* getIndexMatrix();
private:
    void drawGrid();            // helper method used for drawing lines between each cell row/col
    const uint offsetX = (WIDTH - GRID_COLS * DIA_CIRCLE) / 2;
    const uint offsetY = (HEIGHT - GRID_ROWS * DIA_CIRCLE) / 2;
    vector<vector<Rectangle>> cellMatrix;           // needed to determine at which cell a circle is located
    vector<vector<vector<uint>>> indexMatrix;       // every cell has a vector of circle indices located on this cell
};


#endif //PHYSICSSIM_FIXEDGRID_H

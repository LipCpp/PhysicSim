#include "FixedGrid.h"

/*
 * Constructor and Destructor
 */

FixedGrid::FixedGrid()
{
    // init cellMatrix matrix
    float deltaX = 0;
    float deltaY = 0;
    for (int row = 0; row < GRID_ROWS; ++row)
    {
        deltaX = 0;
        vector<Rectangle> tmp;
        for (int col = 0; col < GRID_COLS; ++col)
        {
            tmp.push_back((Rectangle) { offsetX + deltaX,
                                        offsetY + deltaY,
                                        DIA_CIRCLE,
                                        DIA_CIRCLE });

            deltaX += DIA_CIRCLE;
        }
        cellMatrix.push_back(tmp);
        deltaY += DIA_CIRCLE;
    }
}

FixedGrid::~FixedGrid() { }


/*
 * Class methods
 */

void FixedGrid::drawGridCells()
{
    for (int row = 0; row < GRID_ROWS; ++row)
    {
        for (int col = 0; col < GRID_COLS; ++col)
        {
            DrawRectangleRec(cellMatrix.at(row).at(col), GRAY);
        }
    }
    drawGrid();
}

void FixedGrid::drawGrid()
{
    // Watch out!!!  shadowing for offsetX and offsetY
    const uint offsetX = (WIDTH - GRID_COLS * DIA_CIRCLE) / 2 + DIA_CIRCLE;
    const uint offsetY = (HEIGHT - GRID_ROWS * DIA_CIRCLE) / 2 + DIA_CIRCLE;
    uint deltaX = 0;
    uint deltaY = 0;
    Color gridColor = RED;

    // draw horizontal lines
    for (int row = 0; row < GRID_ROWS - 1; ++row)
    {
        DrawLine(offsetX - DIA_CIRCLE,
                 offsetY + deltaY,
                 offsetX - DIA_CIRCLE + GRID_COLS * DIA_CIRCLE,
                 offsetY + deltaY, gridColor);
        deltaY += DIA_CIRCLE;
    }
    // draw vertical lines
    for (int col = 0; col < GRID_COLS - 1; ++col)
    {
        DrawLine(offsetX + deltaX,
                 offsetY - DIA_CIRCLE,
                 offsetX + deltaX,
                 offsetY - DIA_CIRCLE + GRID_ROWS * DIA_CIRCLE, gridColor);
        deltaX += DIA_CIRCLE;
    }

    // TODO: draw borders
}

const uint FixedGrid::getOffsetX() const { return offsetX; }

const uint FixedGrid::getOffsetY() const { return offsetY; }

vector<vector<Rectangle>>* FixedGrid::getCellMatrix() { return &cellMatrix; }

vector<vector<vector<uint>>>* FixedGrid::getIndexMatrix() { return &indexMatrix; }
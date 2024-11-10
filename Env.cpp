#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Env.h"

/*
 * Constructor and Destructor
 */
Env::Env()
{
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetTargetFPS(FPS);
    initRandomObj(NUM_CIRCLES);
    // main loop
    while (!WindowShouldClose())
    {
        // update
        updateGridMatrix();
        updatePos();
        // draw
        BeginDrawing();
        ClearBackground(DARKGRAY);
        fixedGrid.drawGridCells();
        drawCircles();

        checkForColl();
        checkForBorders();
        EndDrawing();
    }
}


/*
 * Class methods
 */
void Env::updateGridMatrix()
{
    for (int row = 0; row < GRID_ROWS; ++row)
    {
        vector<vector<uint>> currRow;
        for (int col = 0; col < GRID_COLS; ++col)
        {
            vector<uint> indicesOnRec;
            for (int i = 0; i < NUM_CIRCLES; ++i)
            {
                Vector2 circleCenter = { circles.at(i).pos.x, circles.at(i).pos.y };
                Rectangle currRec = fixedGrid.getCellMatrix()->at(row).at(col);
                if (CheckCollisionPointRec(circleCenter, currRec))
                {
                    circles.at(i).row = row;
                    circles.at(i).col = col;
                    indicesOnRec.push_back(i);
                }
            }
            currRow.push_back(indicesOnRec);
        }
        fixedGrid.getIndexMatrix()->push_back(currRow);
    }
}


void Env::updatePos()
{
    for (Circle& currCirc : circles)
    {
        currCirc.pos = Vector2Add(currCirc.pos, currCirc.velocity);
    }
}

void Env::checkSurr(uint currIndex)
{
    // calcs dist of two circles
    auto calcDist = [&](uint indexA, uint indexB) -> float
    {
        Vector2 a = { circles.at(indexA).pos.x, circles.at(indexA).pos.y };
        Vector2 b = { circles.at(indexB).pos.x, circles.at(indexB).pos.y };
        return Vector2Distance(a, b);
    };

    // when objects overlap: repel
    auto repel = [&](uint indexA, uint indexB, float dist) -> void
    {
        Vector2 vecA = circles.at(indexA).getPos();
        Vector2 vecB = circles.at(indexB).getPos();
        float overlap = (2 * RAD_CIRCLE - Vector2Length(Vector2Subtract(vecA, vecB))) / 2;
        Vector2 connA = Vector2Subtract(vecA, vecB);
        Vector2 connB = Vector2Subtract(vecB, vecA);
        connA = Vector2Scale(connA, overlap / Vector2Length(connA));
        connB = Vector2Scale(connB, overlap / Vector2Length(connB));
        Vector2 dirA = Vector2Add(vecA, connA);
        Vector2 dirB = Vector2Add(vecB, connB);
#ifdef DEBUG
        DrawLineEx(vecA, dirA, 2, RED);
        DrawLineEx(vecB, dirB, 2, RED);
#endif
        vecA = dirA;
        vecB = dirB;
        circles.at(indexA).setPos(vecA);
        circles.at(indexB).setPos(vecB);
    };

    // check if surrounding cells contain objects
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            try // try to access surrounding cells
            {
                // check if surrounding cell contains objects
                uint currX = circles.at(currIndex).row + x;
                uint currY = circles.at(currIndex).col + y;
                vector<uint> indexVector = fixedGrid.getIndexMatrix()->at(currX).at(currY);
                if (!indexVector.empty())
                {
                    for (uint currIndInVec : indexVector)
                    {
                        // dont compare cell with itself
                        if (currIndex == currIndInVec)
                            continue;
                        float dist = calcDist(currIndex, currIndInVec);
                        if (dist <= DIA_CIRCLE) // Overlap! -> repel
                        {
                            repel(currIndex, currIndInVec, dist);
                        }
                    }
                }

                // check for border collisions

            }
            catch (out_of_range&) { }
        }
    }
}

void Env::checkForColl()
{
    for (int i = 0; i < NUM_CIRCLES; ++i)
    {
        checkSurr(i);
    }
}

void Env::checkForBorders()
{
    uint borderLeftX = 0;
    for (Circle& currCirc : circles)
    {

    }
}

void Env::initRandomObj(const uint numObj)
{
    srand(time(NULL));
    for (int i = 0; i < numObj; ++i)
    {
        float randX = rand() % GRID_WIDTH + fixedGrid.getOffsetX();
        float randY = rand() % GRID_HEIGHT + fixedGrid.getOffsetY();
        circles.push_back((Circle) { (Vector2) { randX, randY },
                    RAD_CIRCLE,
                    (Vector2) { 0, 50 },
                        (uint)i,
                        BLUE });
    }
}

void Env::drawCircles()
{
    for (int i = 0; i < NUM_CIRCLES; ++i)
    {
        DrawCircle(circles.at(i).pos.x,
                   circles.at(i).pos.y,
                   circles.at(i).radius,
                   circles.at(i).color);
    }
}





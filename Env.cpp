#include <iostream>
#include <stdlib.h>
#include <time.h>
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

        // draw
        BeginDrawing();
        ClearBackground(DARKGRAY);
        fixedGrid.drawGridCells();
        drawCircles();
        checkForColl(); // TODO: rename (check + repel in one func)
        updateDirection();
        EndDrawing();
    }
}

Env::~Env() { }


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
                Vector2 circleCenter = { obj.at(i).x, obj.at(i).y };
                Rectangle currRec = fixedGrid.getCellMatrix()->at(row).at(col);
                if (CheckCollisionPointRec(circleCenter, currRec))
                {
#if DEBUG
                    cout << "Index " << i << " located at: row=" << row << " and col=" << col << endl;
#endif
                    obj.at(i).row = row;
                    obj.at(i).col = col;
                    indicesOnRec.push_back(i);
                }
            }
            currRow.push_back(indicesOnRec);
        }
        fixedGrid.getIndexMatrix()->push_back(currRow);
    }

#if DEBUG
    // prints index matrix
    for (int row = 0; row < GRID_ROWS; ++row)
    {
        for (int col = 0; col < GRID_COLS; ++col)
        {
            vector<uint> indicesOnRec = fixedGrid.getIndexMatrix()->at(row).at(col);
            cout << "[";
            uint tabCtr = 4;
            for (int i = 0; i < indicesOnRec.size(); ++i)
            {
                cout << indicesOnRec.at(i) << ", ";
                tabCtr--;
            }
            cout << "]";
            for (int i = 0; i < tabCtr; ++i)
                cout << "\t";
        }
        cout << endl;
    }
#endif
}

void Env::updateDirection()
{
    for (int i = 0; i < NUM_CIRCLES; ++i)
    {
//        obj.at(i).direction = Vector2Add(obj.at(i).direction,
//                                            obj.at(i).direction);
#if DEBUG
//        DrawLineV(obj.at(i).getPos(),
//                  obj.at(i).getDir(), GREEN);
#endif
    }
}

void Env::checkSurr(uint currIndex)
{
    // calcs dist of two circles
    auto calcDist = [&](uint indexA, uint indexB) -> float
    {
        Vector2 a = { obj.at(indexA).x, obj.at(indexA).y };
        Vector2 b = { obj.at(indexB).x, obj.at(indexB).y };
        return Vector2Distance(a, b);
    };

    // when objects overlap: repel
    auto repel = [&](uint indexA, uint indexB, float dist) -> void
    {
        Vector2 vecA = obj.at(indexA).getPos();
        Vector2 vecB = obj.at(indexB).getPos();
        Vector2 ab = Vector2Lerp(vecA, vecB, 1);
        DrawLineV(vecA, ab, GREEN);
    };

    // check if surrounding cells contain objects
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            try // try to access surrounding cells
            {
                // check if surrounding cell contains objects
                uint currX = obj.at(currIndex).row + x;
                uint currY = obj.at(currIndex).col + y;
                vector<uint> indexVector = fixedGrid.getIndexMatrix()->at(currX).at(currY);
                if (indexVector.size() > 0)
                {
                    for (uint currIndInVec : indexVector)
                    {
                        // dont compare cell with itself
                        if (currIndex == currIndInVec)
                            continue;
                        float dist = calcDist(currIndex, currIndInVec);
                        if (dist <= DIA_CIRCLE) // Overlap! -> repel
                        {
#if DEBUG
                            cout << "currIndex: " << currIndex << " overlapping with index: " << currIndInVec << " dist: " << dist << endl;
#endif
                            repel(currIndex, currIndInVec, dist);
                        }
                    }
                }
            }
            catch (out_of_range&) { continue; }
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

void Env::initRandomObj(const uint numObj)
{
    srand(time(NULL));
#if DEBUG
        cout << "i\t\tx\t\ty" << endl << "---------------------" << endl;
#endif
    for (int i = 0; i < numObj; ++i)
    {
        float randX = rand() % GRID_WIDTH + fixedGrid.getOffsetX();
        float randY = rand() % GRID_HEIGHT + fixedGrid.getOffsetY();
#if DEBUG
            cout << i << "\t\t" << randX << "\t\t" << randY << endl;
#endif
        obj.push_back((Circle) { randX, randY, RAD_CIRCLE, (Vector2) { randX, randY }, (uint)i, BLUE });
    }
}

void Env::drawCircles()
{
    for (int i = 0; i < NUM_CIRCLES; ++i)
    {
        DrawCircle(obj.at(i).x,
                   obj.at(i).y,
                   obj.at(i).radius,
                   obj.at(i).color);
    }
}



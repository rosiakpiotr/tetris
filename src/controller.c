#include "include/controller.h"

void resetGame(SGameModel *model)
{
    for (int x = 0; x < FIELD_WIDTH; x++)
    {
        for (int y = 0; y < FIELD_HEIGHT; y++)
        {
            model->field[x][y] = 0;
        }
    }
}

void rotatePiece(SGameModel model, ERotationStage stage)
{
    // int x, y;
    //  findRotationAxis(model.activePiece, &x, &y);
    //   model.activePiece = model.activePiece[]
}

void findRotationAxisForPiece(const char piece[4][4], int *retX, int *retY)
{
    for (size_t x = 0; x < 4; x++)
    {
        for (size_t y = 0; y < 4; y++)
        {
            if (piece[x][y] == 2)
            {
                *retX = x;
                *retY = y;
                return;
            }
        }
    }
}

void insertPiece(SGameModel *model, int pieceId, int rotAxisX, int rotAxisY, int rotStage)
{
    for (size_t x = 0; x < 4; x++)
    {
        for (size_t y = 0; y < 4; y++)
        {
            int ix = (FIELD_WIDTH - 1) / 2 + x - rotAxisX;
            int iy = FIELD_HEIGHT - 1 - y;
            unsigned char block = 0;
            block |= (x == rotAxisX && y == rotAxisY) << IS_AXIAL;
            block |= (pieces[pieceId][rotStage][x][y] << 4);
            model->field[ix][iy] = block;
        }
    }
}
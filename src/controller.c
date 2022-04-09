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
            unsigned char block = 0;
            unsigned char data = pieces[pieceId][rotStage][x][y];
            if (data)
            {
                block |= (x == rotAxisX && y == rotAxisY) << IS_AXIAL;
                SET_PIECE_ID(block, pieceId);
            }

            int ix = (FIELD_WIDTH - 1) / 2 + x - rotAxisX;
            int iy = FIELD_HEIGHT - 1 - y;
            model->field[ix][iy] = block;
        }
    }
}

void movePieceDown(SGameModel *model)
{
    for (size_t x = 0; x < FIELD_WIDTH - 1; x++)
    {
        for (size_t y = 1; y < FIELD_HEIGHT; y++)
        {
            unsigned char block = model->field[x][y];
            model->field[x][y] = 0;
            if (IS_BLOCK_MOVABLE(block))
            {
                model->field[x][y - 1] = block;
            }
        }
    }
}

void movePiece(SGameModel *model, EDirection dir)
{
    if (dir == LEFT)
    {
        for (size_t x = 0; x < FIELD_WIDTH - 1; x++)
        {
            for (size_t y = 0; y < FIELD_HEIGHT; y++)
            {
                if (IS_BLOCK_MOVABLE(model->field[x + 1][y]))
                {
                    model->field[x][y] = model->field[x + 1][y];
                    model->field[x + 1][y] = 0;
                }
            }
        }
    }

    else if (dir == RIGHT)
    {
        for (size_t x = FIELD_WIDTH - 1; x > 0; x--)
        {
            for (size_t y = 0; y < FIELD_HEIGHT; y++)
            {
                if (IS_BLOCK_MOVABLE(model->field[x - 1][y]))
                {
                    model->field[x][y] = model->field[x - 1][y];
                    model->field[x - 1][y] = 0;
                }
            }
        }
    }
}

char canMove(SGameModel *model, EDirection dir)
{
    if (dir == LEFT)
    {
        for (size_t y = 0; y < FIELD_HEIGHT; y++)
        {
            if (IS_BLOCK_MOVABLE(model->field[0][y]))
            {
                return FALSE;
            }
        }
    }

    else if (dir == RIGHT)
    {
        for (size_t y = 0; y < FIELD_HEIGHT; y++)
        {
            if (IS_BLOCK_MOVABLE(model->field[FIELD_WIDTH - 1][y]))
            {
                return FALSE;
            }
        }
    }

    return TRUE;
}
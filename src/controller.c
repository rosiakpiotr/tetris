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

void insertNextPiece(SGameModel *model, int xOff)
{
    for (size_t x = 0; x < 4; x++)
    {
        for (size_t y = 0; y < 4; y++)
        {
            unsigned char block = model->next[x][y];
            char axis = block & (1 << IS_RAXIS);

            int ix = (FIELD_WIDTH - 1) / 2 + x - xOff;
            int iy = FIELD_HEIGHT - 1 - y;
            model->field[ix][iy] = block;
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

    else if (dir == DOWN)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            for (int y = 0; y < FIELD_HEIGHT - 1; y++)
            {
                if (IS_BLOCK_MOVABLE(model->field[x][y + 1]))
                {
                    model->field[x][y] = model->field[x][y + 1];
                    model->field[x][y + 1] = 0;
                }
            }
        }
    }
}

char willCrossBoundaries(SGameModel *model, EDirection dir)
{
    if (dir == LEFT)
    {
        for (size_t y = 0; y < FIELD_HEIGHT; y++)
        {
            if (IS_BLOCK_MOVABLE(model->field[0][y]))
            {
                return SIDE_TOUCH;
            }
        }
    }

    else if (dir == RIGHT)
    {
        for (size_t y = 0; y < FIELD_HEIGHT; y++)
        {
            if (IS_BLOCK_MOVABLE(model->field[FIELD_WIDTH - 1][y]))
            {
                return SIDE_TOUCH;
            }
        }
    }

    else if (dir == DOWN)
    {
        for (size_t x = 0; x < FIELD_WIDTH; x++)
        {
            if (IS_BLOCK_MOVABLE(model->field[x][0]))
            {
                return GROUND_TOUCH;
            }
        }
    }

    return FALSE;
}

char collisionCheck(SGameModel *model, EDirection dir)
{
    int xoff = dir == LEFT ? 1 : dir == RIGHT ? -1
                                              : 0;
    int yoff = dir == DOWN;
    for (size_t x = 1; x < FIELD_WIDTH - 1; x++)
    {
        for (size_t y = 1; y < FIELD_HEIGHT - 1; y++)
        {
            unsigned char data = model->field[x][y];
            if (IS_BLOCK_MOVABLE(data))
            {
                unsigned char next = model->field[x][y - yoff];
                if (next & (1 << COLLIDED))
                {
                    return GROUND_TOUCH;
                }
                next = model->field[x - xoff][y];
                if (next & (1 << COLLIDED))
                {
                    return SIDE_TOUCH;
                }
            }
        }
    }

    return FALSE;
}

void collidePiece(SGameModel *model)
{
    for (size_t x = 0; x < FIELD_WIDTH; x++)
    {
        for (size_t y = 0; y < FIELD_HEIGHT; y++)
        {
            unsigned char block = model->field[x][y];
            if (IS_BLOCK_MOVABLE(block))
            {
                block |= (1 << COLLIDED);
                model->field[x][y] = block;
            }
        }
    }
}

void chooseNextPiece(SGameModel *model, int *computedXOffset)
{
    // Random int between 0 and 6
    int id = rand() % 7;
    int stage = rand() % 4;

    int xax, yax;
    findRotationAxisForPiece(pieces[id][stage], &xax, &yax);
    *computedXOffset = xax;

    for (size_t x = 0; x < 4; x++)
    {
        for (size_t y = 0; y < 4; y++)
        {
            unsigned char data = pieces[id][stage][x][y];
            unsigned char block = 0;
            if (data)
            {
                block |= (x == xax && y == yax) << IS_RAXIS;
                // Extract only first 3 bits
                block |= (stage & 0x3) << ROT_STAG;
                SET_PIECE_ID(block, id);
            }
            model->next[x][y] = block;
        }
    }
}
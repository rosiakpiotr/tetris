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

void rotatePiece(SGameModel *model)
{
    // Remove current piece and insert new one with next rotation stage
    // ensuring match between rotation axis blocks
    /*char id;
    char rotstage;
    char prevxax, prevyax;

    for (int x = 0; x < FIELD_WIDTH; x++)
    {
        for (int y = 0; y < FIELD_HEIGHT; y++)
        {
            unsigned char block = model->field[x][y];
            if (IS_BMOVABLE(block))
            {
                id = GET_PIECE_ID(block);
                rotstage = GET_ROT_STAGE(block);
                if (block & (1 << IS_RAXIS))
                {
                    prevxax = x;
                    prevyax = y;
                }
                model->field[x][y] = 0;
            }
        }
    }

    unsigned char next[4][4];
    unsigned char field[FIELD_WIDTH][FIELD_HEIGHT];
    memcpy(next, model->next, sizeof(model->next));
    memcpy(field, model->field, sizeof(model->field));

    int targxax, targyax;
    chooseNextPiece(model, &targxax, &targyax, id, (rotstage + 1) % 4);*/
    // int yyyy = FIELD_HEIGHT - prevyax + targyax; // FIELD_HEIGHT - prevyax;
    //  printf("Y local: %d\n", targyax);

    // printf("Could: %d\n", x);

    // memcpy(model->field, field, sizeof(field));

    // printf("Axis location before rotation: %d, %d, want move by: %d, %d\n", prevxax, prevyax, xxxx, yyyy);

    // memcpy(model->next, next, sizeof(next));
}

char insertNext(SGameModel *model, int xoffset, int yoffset)
{
    unsigned char block;
    unsigned char data;
    int fieldX;
    int fieldY;
    for (size_t x = 0; x < PIECE_SIZE; x++)
    {
        for (size_t y = 0; y < PIECE_SIZE; y++)
        {
            block = model->next[x][y];
            if (!block)
                continue;
            fieldX = x + xoffset;
            fieldY = y + yoffset;
            if (!X_INDEX_IN_RANGE(fieldX) || !Y_INDEX_IN_RANGE(fieldY))
                return FALSE;
            data = model->field[fieldX][fieldY];
            if (data != EMPTY_BLOCK)
                return FALSE;
            model->field[fieldX][fieldY] = block;
        }
    }

    return TRUE;
}

void movePiece(SGameModel *model, EDirection dir)
{
    if (dir == LEFT)
    {
        for (size_t x = 0; x < FIELD_WIDTH - 1; x++)
        {
            for (size_t y = 0; y < FIELD_HEIGHT; y++)
            {
                if (IS_BMOVABLE(model->field[x + 1][y]))
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
                if (IS_BMOVABLE(model->field[x - 1][y]))
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
                if (IS_BMOVABLE(model->field[x][y + 1]))
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
            if (IS_BMOVABLE(model->field[0][y]))
            {
                return SIDE_TOUCH;
            }
        }
    }

    else if (dir == RIGHT)
    {
        for (size_t y = 0; y < FIELD_HEIGHT; y++)
        {
            if (IS_BMOVABLE(model->field[FIELD_WIDTH - 1][y]))
            {
                return SIDE_TOUCH;
            }
        }
    }

    else if (dir == DOWN)
    {
        for (size_t x = 0; x < FIELD_WIDTH; x++)
        {
            if (IS_BMOVABLE(model->field[x][0]))
            {
                return GROUND_TOUCH;
            }
        }
    }

    return FALSE;
}

char collisionCheck(SGameModel *model, EDirection dir)
{
    /*int xoff = dir == LEFT ? 1 : dir == RIGHT ? -1
                                              : 0;
    int yoff = dir == DOWN;
    for (size_t x = 1; x < FIELD_WIDTH - 1; x++)
    {
        for (size_t y = 1; y < FIELD_HEIGHT - 1; y++)
        {
            unsigned char data = model->field[x][y];
            if (IS_BMOVABLE(data))
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
    }*/

    return FALSE;
}

void collidePiece(SGameModel *model)
{
    /*for (size_t x = 0; x < FIELD_WIDTH; x++)
    {
        for (size_t y = 0; y < FIELD_HEIGHT; y++)
        {
            unsigned char block = model->field[x][y];
            if (IS_BMOVABLE(block))
            {
                block |= (1 << COLLIDED);
                model->field[x][y] = block;
            }
        }
    }*/
}

void prepareNext(SGameModel *model, int id, int rotation)
{
    unsigned char data;
    unsigned char block;
    for (size_t x = 0; x < PIECE_SIZE; x++)
    {
        for (size_t y = 0; y < PIECE_SIZE; y++)
        {
            data = pieces[id][rotation][x][y];
            block = 0;
            SET_MOVABLE(block, TRUE);
            SET_PIECE_ID(block, id);
            SET_ROTATION(block, rotation);
            SET_IS_AXIS(block, data == AXIS_OF_ROTATION);
            block = data ? block : EMPTY_BLOCK;
            model->next[x][y] = block;
            model->nextLocalAxisX = IS_ROT_AXIS(block) ? x : model->nextLocalAxisX;
            model->nextLocalAxisY = IS_ROT_AXIS(block) ? y : model->nextLocalAxisY;
        }
    }
}

void prepareRandomNext(SGameModel *model)
{
    int id = rand() % PIECE_COUNT;
    int rotation = rand() % ROTATION_COUNT;

    prepareNext(model, id, rotation);
}

void clearRows(SGameModel *model)
{
    /*for (size_t y = 0; y < FIELD_HEIGHT; y++)
    {
        char rowCollided = TRUE;
        for (size_t x = 0; x < FIELD_WIDTH; x++)
        {
            unsigned char block = model->field[x][y];
            if (!(block & (1 << COLLIDED)))
                rowCollided = FALSE;
        }

        if (rowCollided)
        {
            for (size_t x = 0; x < FIELD_WIDTH; x++)
                model->field[x][y] = 0;
        }
    }*/
}
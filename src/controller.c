#include "include/controller.h"

unsigned char nextBackup[PIECE_SIZE][PIECE_SIZE];
unsigned char fieldBackup[FIELD_WIDTH][FIELD_HEIGHT];

void backupNext(SGameModel *model)
{
    memcpy(nextBackup, model->next, sizeof(model->next));
}
void restoreNext(SGameModel *model)
{
    memcpy(model->next, nextBackup, sizeof(nextBackup));
}
void backupField(SGameModel *model)
{
    memcpy(fieldBackup, model->field, sizeof(model->field));
}
void restoreField(SGameModel *model)
{
    memcpy(model->field, fieldBackup, sizeof(fieldBackup));
}

void resetGame(SGameModel *model)
{
    for (size_t y = 0; y < FIELD_HEIGHT; y++)
    {
        for (size_t x = 0; x < FIELD_WIDTH; x++)
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
    int fieldX;
    int fieldY;
    for (size_t y = 0; y < PIECE_SIZE; y++)
    {
        for (size_t x = 0; x < PIECE_SIZE; x++)
        {
            block = model->next[x][y];
            if (!block)
                continue;
            fieldX = x + xoffset;
            fieldY = y + yoffset;
            if (!INDEXES_IN_RANGE(fieldX, fieldY) || model->field[fieldX][fieldY] != EMPTY_BLOCK)
                return FALSE;
            model->field[fieldX][fieldY] = block;
        }
    }

    return TRUE;
}

void findCurrentAxisInField(SGameModel *model, int *xIndex, int *yIndex)
{
    for (size_t y = 0; y < FIELD_HEIGHT; y++)
    {
        for (size_t x = 0; x < FIELD_WIDTH; x++)
        {
            if (IS_ROT_AXIS(model->field[x][y]))
            {
                *xIndex = x;
                *yIndex = y;
                return;
            }
        }
    }
}

void eraseCurrentPieceStartingAt(SGameModel *model, int xIndex, int yIndex)
{
    for (size_t y = 0; y < PIECE_SIZE; y++)
    {
        for (size_t x = 0; x < PIECE_SIZE; x++)
        {
            if (INDEXES_IN_RANGE(xIndex + x, yIndex + y) &&
                IS_BMOVABLE(model->field[xIndex + x][yIndex + y]))
            {
                model->field[xIndex + x][yIndex + y] = 0;
            }
        }
    }
}

char moveCurrent(SGameModel *model, EDirection dir)
{
    char success;
    int rotCentX;
    int rotCentY;
    int xoffset = dir == LEFT ? -1 : dir == RIGHT ? 1
                                                  : 0;
    int yoffset = dir == DOWN ? 1 : 0;

    backupNext(model);
    backupField(model);

    findCurrentAxisInField(
        model,
        &rotCentX,
        &rotCentY);
    eraseCurrentPieceStartingAt(
        model,
        rotCentX - model->nextLocalAxisX,
        rotCentY - model->nextLocalAxisY);
    prepareNext(
        model,
        GET_PIECE_ID(model->field[rotCentX][rotCentY]),
        GET_ROTATION(model->field[rotCentX][rotCentY]));
    success = insertNext(
        model,
        rotCentX - model->nextLocalAxisX + xoffset,
        rotCentY - model->nextLocalAxisY + yoffset);
    if (!success)
        restoreField(model);
    restoreNext(model);
    return success;
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
    for (size_t y = 0; y < PIECE_SIZE; y++)
    {
        for (size_t x = 0; x < PIECE_SIZE; x++)
        {
            data = pieces[id][rotation][y][x];
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
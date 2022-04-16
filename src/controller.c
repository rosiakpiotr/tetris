#include "include/controller.h"

void resetGame(SGameModel *model)
{
    for (size_t y = 0; y < FIELD_HEIGHT; y++)
        for (size_t x = 0; x < FIELD_WIDTH; x++)
            model->field[x][y] = EMPTY_BLOCK;
}

char attemptMoveCurrent(SGameModel *model, EDirection dir)
{
    return attemptTransform(model, 1, dir, 0);
}

char attemptRotateCurrent(SGameModel *model)
{
    return attemptTransform(model, 0, DOWN, 1);
}

char attemptTransform(SGameModel *model, int moveBy, EDirection dir, int rotateTimes)
{
    char success;
    SPiece nextBackup;
    TGameField fieldBackup;

    // Backup field and next piece in case move fails
    memcpy(&nextBackup, &model->next, sizeof(model->next));
    memcpy(&fieldBackup, model->field, sizeof(model->field));

    success = transformCurrent(model, moveBy, dir, rotateTimes);
    // Restore last state of game field if move failed and always restore
    // next piece that was there before doing movement.
    if (!success)
        memcpy(model->field, &fieldBackup, sizeof(fieldBackup));
    memcpy(&model->next, &nextBackup, sizeof(nextBackup));

    return success;
}

char transformCurrent(SGameModel *model, int moveBy, EDirection dir, int rotateTimes)
{
    int rotCentX;
    int rotCentY;
    int xoffset = moveBy * (dir == LEFT ? -1 : (dir == RIGHT ? 1 : 0));
    int yoffset = moveBy * (dir == DOWN ? 1 : 0);

    findCurrentAxisInField(
        model,
        &rotCentX,
        &rotCentY);
    prepareNext(
        model,
        (GET_PIECE_ID(model->field[rotCentX][rotCentY])),
        (GET_ROTATION((model->field[rotCentX][rotCentY])) + rotateTimes) % ROTATION_COUNT);
    eraseCurrent(model);
    return insertNext(
        model,
        rotCentX - model->next.localAxisX + xoffset,
        rotCentY - model->next.localAxisY + yoffset);
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
            block = model->next.data[x][y];
            if (block == EMPTY_BLOCK)
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
            if (IS_BMOVABLE(model->field[x][y]) && IS_ROT_AXIS(model->field[x][y]))
            {
                *xIndex = x;
                *yIndex = y;
                return;
            }
        }
    }
}

void eraseCurrent(SGameModel *model)
{
    for (size_t y = 0; y < FIELD_HEIGHT; y++)
    {
        for (size_t x = 0; x < FIELD_WIDTH; x++)
        {
            if (IS_BMOVABLE(model->field[x][y]))
            {
                model->field[x][y] = EMPTY_BLOCK;
            }
        }
    }
}

void immobiliseCurrent(SGameModel *model)
{
    for (size_t y = 0; y < FIELD_HEIGHT; y++)
        for (size_t x = 0; x < FIELD_WIDTH; x++)
            SET_INMOVABLE(model->field[x][y]);
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
            block = EMPTY_BLOCK;
            SET_MOVABLE(block);
            SET_PIECE_ID(block, id);
            SET_ROTATION(block, rotation);
            if (data == AXIS_OF_ROTATION)
                SET_IS_AXIS(block);
            SET_PRESENT(block);
            block = data ? block : EMPTY_BLOCK;
            model->next.data[x][y] = block;
            model->next.localAxisX = IS_ROT_AXIS(block) ? x : model->next.localAxisX;
            model->next.localAxisY = IS_ROT_AXIS(block) ? y : model->next.localAxisY;
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
    char rowCollided;
    for (size_t y = 0; y < FIELD_HEIGHT; y++)
    {
        rowCollided = TRUE;
        for (size_t x = 0; x < FIELD_WIDTH; x++)
        {
            if (!IS_PRESENT(model->field[x][y]) || IS_BMOVABLE(model->field[x][y]))
            {
                rowCollided = FALSE;
            }
        }
        if (rowCollided)
        {
            for (size_t x = 0; x < FIELD_WIDTH; x++)
            {
                model->field[x][y] = EMPTY_BLOCK;
            }
        }
    }
}
#ifndef TYPES_H
#define TYPES_H

#include "primlib.h"
#include "constants.h"

typedef enum color EColor;
typedef unsigned char TGameField[FIELD_WIDTH][FIELD_HEIGHT];

typedef enum
{
    LEFT,
    RIGHT,
    DOWN
} EDirection;

typedef struct
{
    int localAxisX;
    int localAxisY;
    unsigned char data[PIECE_SIZE][PIECE_SIZE];
} SPiece;

typedef struct
{
    TGameField field;
    SPiece next;
} SGameModel;

#endif
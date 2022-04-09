#ifndef TYPES_H
#define TYPES_H

#include "primlib.h"
#include "constants.h"

typedef enum color EColor;

typedef enum
{
    FIRST,
    SECOND,
    THIRD,
    FOURTH
} ERotationStage;

typedef struct
{
    unsigned char field[FIELD_WIDTH][FIELD_HEIGHT];
} SGameModel;

#endif
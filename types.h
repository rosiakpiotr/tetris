#ifndef TYPES_H
#define TYPES_H

#include "constants.h"

typedef enum color EColor;
typedef struct
{
    int field[FIELD_WIDTH][FIELD_HEIGHT];
} SGameModel;

#endif
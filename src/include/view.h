#ifndef VIEW_H
#define VIEW_H

#include "constants.h"
#include "types.h"
#include "utility.h"

void drawBlock(int xCenter, int yCenter, int width, EColor color);
void drawBoard(SGameModel model);
void clearScreen();

#endif
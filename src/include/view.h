#ifndef VIEW_H
#define VIEW_H

#include "constants.h"
#include "types.h"

void drawGame(SGameModel model);

void drawBlock(int xCenter, int yCenter, int width, EColor color);
void drawBoard(SGameModel model);
void drawPegs();
void drawNext(SGameModel model);

void clearScreen();

#endif
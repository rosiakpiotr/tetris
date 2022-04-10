#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>
#include <time.h>

#include "types.h"
#include "constants.h"
#include "piece_definition.h"
#include "utility.h"

void resetGame(SGameModel *model);
void rotatePiece();
void findRotationAxisForPiece(const char piece[4][4], int *retX, int *retY);
void insertPiece(SGameModel *model, int pieceId, int rotAxisX, int rotAxisY, int rotStage);
void movePiece(SGameModel *model, EDirection dir);
char willCrossBoundaries(SGameModel *model, EDirection dir);
char collisionCheck(SGameModel *model, EDirection dir);
void collidePiece(SGameModel *model);

void chooseNextPiece(SGameModel *model, int *computedXOffset);
void insertNextPiece(SGameModel *model, int xoffset);

#endif
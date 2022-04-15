#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>
#include <time.h>

#include "types.h"
#include "constants.h"
#include "piece_definition.h"

void backupNext(SGameModel *model);
void restoreNext(SGameModel *model);
void backupField(SGameModel *model);
void restoreField(SGameModel *model);

void resetGame(SGameModel *model);
void rotatePiece(SGameModel *model);
char moveCurrent(SGameModel *model, EDirection dir);
void findCurrentAxisInField(SGameModel *model, int *xIndex, int *yIndex);
void eraseCurrentPieceStartingAt(SGameModel *model, int xIndex, int yIndex);
void collidePiece(SGameModel *model);

void prepareRandomNext(SGameModel *model);
void prepareNext(SGameModel *model, int id, int rotation);

// Inserts next piece until detects collision with field bounds or other blocks.
// Returns TRUE on successfull insertion (all non zero blocks from next piece are inserted)
// Returns FALSE if piece was about to cover different non zero block or violate game array boundaries.
char insertNext(SGameModel *model, int xoffset, int yoffset);

void clearRows(SGameModel *model);

#endif
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>
#include <time.h>

#include "types.h"
#include "constants.h"
#include "piece_definition.h"

void resetGame(SGameModel *model);
void rotatePiece(SGameModel *model);
void movePiece(SGameModel *model, EDirection dir);
char willCrossBoundaries(SGameModel *model, EDirection dir);
char collisionCheck(SGameModel *model, EDirection dir);
void collidePiece(SGameModel *model);

void prepareRandomNext(SGameModel *model);
void prepareNext(SGameModel *model, int id, int rotation);

// Inserts next piece until detects collision with field bounds or other blocks.
// Returns TRUE on successfull insertion (all non zero blocks from next piece are inserted)
// Returns FALSE if piece was about to cover different non zero block or violate game array boundaries.
char insertNext(SGameModel *model, int xoffset, int yoffset);

void clearRows(SGameModel *model);

#endif
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "types.h"
#include "constants.h"
#include "piece_definition.h"
#include "utility.h"

void resetGame(SGameModel *model);
void rotatePiece();
void findRotationAxisForPiece(const char piece[4][4], int *retX, int *retY);
void insertPiece(SGameModel *model, int pieceId, int rotAxisX, int rotAxisY, int rotStage);
void movePieceDown(SGameModel *model);
void movePiece(SGameModel *model, EDirection dir);
char canMove(SGameModel *model, EDirection dir);

#endif
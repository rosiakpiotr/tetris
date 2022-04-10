#ifndef CONSTANTS_H
#define CONSTANTS_H

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

#define BLOCK_DIMENSION 20

#define FRAMERATE 60
#define FRAMERATE_DELAY 1000 / FRAMERATE

#define AXIS_OF_ROTATION 2

#define SIDE_TOUCH 1
#define GROUND_TOUCH 2

/* Block bitshifts */
#define COLLIDED 0 // 0x01 -> 00000001
#define PIECE_ID 1 // 0x0E -> 00001110
#define ROT_STAG 4 // 0x70 -> 01110000
#define IS_RAXIS 7 // 0x80 -> 10000000

#endif
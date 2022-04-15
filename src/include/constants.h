#ifndef CONSTANTS_H
#define CONSTANTS_H

/*******************************************/
/* RENDERING AND APPEARANCE -------------- */
/* --------------------------------------- */
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define BLOCK_DIMENSION 20
#define BLOCK_SPACING 5
#define FRAMERATE 60
#define FRAMERATE_DELAY 1000 / FRAMERATE
/*******************************************/

/*******************************************/
/* PIECE DEFINITION ---------------------- */
/* --------------------------------------- */
#define PIECE_SIZE 4
#define PIECE_COUNT 7
#define ROTATION_COUNT 4
#define AXIS_OF_ROTATION 2
/*******************************************/

/*******************************************/
/* INTERNALS ----------------------------- */
/* --------------------------------------- */
#define SIDE_TOUCH 1
#define GROUND_TOUCH 2
#define TOP_TOUCH 3

/* Block bitshifts */
#define BMOVABLE 0 // 00000001 -> 1 bit
#define PIECE_ID 1 // 00001110 -> 3 bits
#define ROTATION 4 // 00110000 -> 2 bits
#define IS_RAXIS 6 // 01000000 -> 1 bit

#define IS_BMOVABLE(BLOCK) (BLOCK & (1 << BMOVABLE))
#define SET_MOVABLE(BLOCK, FLAG) (BLOCK |= (((FLAG)&0x01) << BMOVABLE)) // 0x01 -> 0000 0001
#define GET_PIECE_ID(BLOCK) ((BLOCK >> PIECE_ID) & ((1 << 3) - 1))
#define SET_PIECE_ID(BLOCK, ID) (BLOCK |= (((ID)&0x07) << PIECE_ID)) // 0x07 -> 0000 0111
#define GET_ROTATION(BLOCK) ((BLOCK >> ROTATION) & ((1 << 2) - 1))
#define SET_ROTATION(BLOCK, STAGE) (BLOCK |= (((STAGE)&0x03) << ROTATION)) // 0x03 -> 0000 0011
#define IS_ROT_AXIS(BLOCK) (BLOCK & (1 << IS_RAXIS))
#define SET_IS_AXIS(BLOCK, FLAG) (BLOCK |= (((FLAG)&0x01) << IS_RAXIS))

#define X_INDEX_IN_RANGE(INDEX) ((INDEX) >= 0 && (INDEX) < FIELD_WIDTH)
#define Y_INDEX_IN_RANGE(INDEX) ((INDEX) >= 0 && (INDEX) < FIELD_HEIGHT)

#define TRUE 1
#define FALSE 0

#define EMPTY_BLOCK 0x00
#define INVALID -1
/*******************************************/

#endif
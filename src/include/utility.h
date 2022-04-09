#ifndef UTILITY_H
#define UTILITY_H

#define IS_BLOCK_MOVABLE(BLOCK) ((BLOCK & (((1 << 3) - 1) << PIECE_ID)) && !((BLOCK & (((1 << 1) - 1) << COLLIDED))))

// Piece ID is offset by 1 so 3 bits responsible for piece ID are never 0 if piece is present.
#define GET_PIECE_ID(BLOCK) (((n >> PIECE_ID) & ((1 << 3) - 1)) - 1)
#define SET_PIECE_ID(BLOCK, ID) (BLOCK |= ((ID + 1) << PIECE_ID))

#endif
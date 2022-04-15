#include "include/view.h"

void drawBlock(int xCenter, int yCenter, int width, EColor color)
{
    int half = width / 2;
    gfx_filledRect(
        xCenter - half,
        yCenter - half,
        xCenter + half,
        yCenter + half,
        color);
}

void drawBoard(SGameModel model)
{
    unsigned char block;
    EColor color;
    int dx = (BLOCK_DIMENSION + BLOCK_SPACING);
    int dy = (BLOCK_DIMENSION + BLOCK_SPACING);

    for (size_t y = 0; y < FIELD_HEIGHT; y++)
    {
        for (size_t x = 0; x < FIELD_WIDTH; x++)
        {
            block = model.field[x][y];
            color = GREEN;
            if (IS_BMOVABLE(block))
            {
                color = YELLOW;
                if (IS_ROT_AXIS(block))
                    color = RED;
            }
            else if (block != EMPTY_BLOCK)
                color = BLACK;

            drawBlock(
                x * dx + 50,
                y * dy + 100,
                BLOCK_DIMENSION,
                color);
        }
    }
}

void clearScreen()
{
    gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
}
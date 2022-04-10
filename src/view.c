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
    int dx = (BLOCK_DIMENSION + 5);
    int dy = (BLOCK_DIMENSION + 5);
    for (int x = 0; x < FIELD_WIDTH; x++)
    {
        for (int y = 0; y < FIELD_HEIGHT; y++)
        {
            unsigned char block = model.field[x][y];
            unsigned char is_axial = block & (1 << IS_RAXIS);
            unsigned char collided = block & (1 << COLLIDED);
            EColor color = GREEN;
            if (IS_BLOCK_MOVABLE(block))
            {
                color = YELLOW;
                if (is_axial)
                    color = RED;
            }
            else if (collided)
                color = BLACK;

            drawBlock(
                x * dx + 50,
                FIELD_HEIGHT * dy - y * dy + 100,
                BLOCK_DIMENSION,
                color);
        }
    }
}

void clearScreen()
{
    gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
}
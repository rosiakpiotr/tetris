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
            unsigned char data = model.field[x][y];
            unsigned char is_axial = data & (1 << IS_AXIAL);
            if (data)
            {
                int xerino = 5;
            }
            drawBlock(
                x * dx + 50,
                FIELD_HEIGHT * dy - y * dy + 100,
                BLOCK_DIMENSION,
                is_axial ? RED : (data > 0 ? YELLOW : GREEN));
        }
    }
}

void clearScreen()
{
    gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
}
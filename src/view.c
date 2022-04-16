#include "include/view.h"

void drawGame(SGameModel model)
{
    drawPegs();
    drawBoard(model);
    drawNext(model);
}

void drawPegs()
{
    gfx_line(
        LEFT_PEG_LOC - 1,
        gfx_screenHeight(),
        LEFT_PEG_LOC - 1,
        gfx_screenHeight() - PEG_HEIGHT,
        YELLOW);

    gfx_line(
        RIGHT_PEG_LOC,
        gfx_screenHeight(),
        RIGHT_PEG_LOC,
        gfx_screenHeight() - PEG_HEIGHT,
        YELLOW);
}

void drawBlock(int xCenter, int yCenter, int width, EColor color)
{
    int half = width / 2.f;
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
            color = BLACK;
            if (IS_BMOVABLE(block))
            {
                color = GREEN;
                if (IS_ROT_AXIS(block))
                    color = YELLOW;
            }
            else if (block != EMPTY_BLOCK)
                color = RED;

            drawBlock(
                x * dx + LEFT_PEG_LOC + BLOCK_DIMENSION / 2,
                y * dy + (gfx_screenHeight() - PEG_HEIGHT + BLOCK_DIMENSION / 2),
                BLOCK_DIMENSION,
                color);
        }
    }
}

void drawNext(SGameModel model)
{
    unsigned char block;
    EColor color;
    int dx = (BLOCK_DIMENSION + BLOCK_SPACING);
    int dy = (BLOCK_DIMENSION + BLOCK_SPACING);
    for (size_t y = 0; y < PIECE_SIZE; y++)
    {
        for (size_t x = 0; x < PIECE_SIZE; x++)
        {
            block = model.next.data[x][y];
            color = BLACK;
            if (IS_BMOVABLE(block))
            {
                color = GREEN;
                if (IS_ROT_AXIS(block))
                    color = YELLOW;
            }
            drawBlock(
                x * dx + RIGHT_PEG_LOC + 200,
                y * dy + 200,
                BLOCK_DIMENSION,
                color);
        }
    }
}

void drawFinalText()
{
    gfx_textout(gfx_screenWidth() / 2, gfx_screenHeight() / 2, FINAL_TEXT, YELLOW);
}

void clearScreen()
{
    gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
}
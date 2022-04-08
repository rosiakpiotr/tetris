#include "primlib.h"
#include "constants.h"

void drawBlock(int x, int y, enum color color)
{
    int halfBlock = BLOCK_DIMENSION / 2;
    gfx_filledRect(x - halfBlock, y - halfBlock, x + halfBlock, y + halfBlock, color);
}

void drawBoard()
{
    for (size_t x = 0; x < FIELD_WIDTH; x++)
    {
        for (size_t y = 0; y < FIELD_HEIGHT; y++)
        {
            // drawBlock(x, y, RED)
        }
    }
}

void clearScreen()
{
    gfx_filledRect(0, 0, gfx_screenWidth() - 1, gfx_screenHeight() - 1, BLACK);
}

int main()
{
    if (gfx_init() != 0)
    {
        printf("Failed to initialize window.\n");
        exit(1);
    }
    int gameArray[FIELD_WIDTH][FIELD_HEIGHT];
    printf("%d", gfx_pollkey());
    while (1)
    {
        int key = gfx_pollkey();
        if (key == SDLK_ESCAPE)
            break;
        clearScreen();
        drawBoard();
        gfx_updateScreen();
        SDL_Delay(FRAMERATE_DELAY);
    }
    printf("Press any key to finish");
    gfx_getkey();
    return 0;
}
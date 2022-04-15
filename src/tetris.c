#include <time.h>

#include "include/primlib.h"
#include "include/types.h"
#include "include/controller.h"
#include "include/view.h"
#include "include/piece_definition.h"

int main()
{
    if (gfx_init() != 0)
    {
        printf("Failed to initialize window.\n");
        exit(1);
    }

    srand(time(NULL));

    SGameModel model;
    resetGame(&model);
    prepareRandomNext(&model);

    int counter = 0;
    char hasPiece = FALSE;
    char gameOver = FALSE;
    while (1)
    {
        int key = gfx_pollkey();

        clearRows(&model);

        if (!hasPiece && !gameOver)
        {
            char success = insertNext(&model, FIELD_WIDTH / 2 - 1 - model.nextLocalAxisX, 0);
            if (!success)
            {
                collidePiece(&model);
                gameOver = TRUE;
                hasPiece = FALSE;
            }
            else
            {
                prepareRandomNext(&model);
                hasPiece = TRUE;
            }
        }

        if (hasPiece && key == SDLK_LEFT)
        {
            moveCurrent(&model, LEFT);
        }

        else if (hasPiece && key == SDLK_RIGHT)
        {
            moveCurrent(&model, RIGHT);
        }

        else if (hasPiece && key == SDLK_DOWN)
        {
        }

        if (key == SDLK_SPACE)
        {
            rotatePiece(&model);
        }

        if (counter++ == 20)
        {
            moveCurrent(&model, DOWN);
            counter = 0;
        }

        clearScreen();
        drawBoard(model);
        gfx_updateScreen();
        SDL_Delay(FRAMERATE_DELAY);
    }

    return 0;
}
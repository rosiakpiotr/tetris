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

    int counter = 0;
    char inserted = forwardPieces(&model);
    EGameState state;
    while (1)
    {
        int key = gfx_pollkey();
        if (state == GOING)
        {
            if (key == SDLK_LEFT)
                attemptMoveCurrent(&model, LEFT);

            else if (key == SDLK_RIGHT)
                attemptMoveCurrent(&model, RIGHT);

            else if (key == SDLK_DOWN)
                while ((inserted = attemptMoveCurrent(&model, DOWN)) == TRUE)
                    ;

            if (key == SDLK_SPACE)
                attemptRotateCurrent(&model);

            if (counter++ == MOVE_DOWN_EVERY_N_FRAMES)
            {
                clearRows(&model);
                inserted = attemptMoveCurrent(&model, DOWN);
                counter = 0;
            }

            if (!inserted)
            {
                immobiliseCurrent(&model);
                inserted = forwardPieces(&model);
                if (!inserted)
                    state = OVER;
            }
        }
        else if (state == OVER)
        {
            if (key == SDLK_RETURN)
            {
                resetGame(&model);
                inserted = forwardPieces(&model);
                state = GOING;
            }
            else if (key == SDLK_ESCAPE)
            {
                break;
            }
        }

        clearScreen();
        if (state == GOING)
        {
            drawGame(model);
            drawBoard(model);
        }
        else if (state == OVER)
        {
            drawFinalText();
        }
        gfx_updateScreen();
        SDL_Delay(FRAMERATE_DELAY);
    }

    return 0;
}
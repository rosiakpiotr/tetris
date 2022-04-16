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
    insertNext(&model, FIELD_WIDTH / 2 - 1 - model.next.localAxisX, 0);

    int counter = 0;
    char movePerfomed = TRUE;
    while (1)
    {
        int key = gfx_pollkey();

        if (key == SDLK_LEFT)
        {
            attemptMoveCurrent(&model, LEFT);
        }

        else if (key == SDLK_RIGHT)
        {
            attemptMoveCurrent(&model, RIGHT);
        }

        else if (key == SDLK_DOWN)
        {
            while ((movePerfomed = attemptMoveCurrent(&model, DOWN)) != FALSE)
                ;
        }

        if (key == SDLK_SPACE)
        {
            attemptRotateCurrent(&model);
        }

        if (counter++ == 20)
        {
            if (movePerfomed)
                clearRows(&model);
            movePerfomed = attemptMoveCurrent(&model, DOWN);
            counter = 0;
        }

        if (!movePerfomed)
        {
            immobiliseCurrent(&model);
            prepareRandomNext(&model);
            movePerfomed = insertNext(&model, FIELD_WIDTH / 2 - 1 - model.next.localAxisX, 0);
            if (!movePerfomed)
                break;
        }

        clearScreen();
        drawBoard(model);
        gfx_updateScreen();
        SDL_Delay(FRAMERATE_DELAY);
    }

    return 0;
}
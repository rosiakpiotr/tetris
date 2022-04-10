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
    int xoffset;
    chooseNextPiece(&model, &xoffset);

    int counter = 0;
    EDirection moveDir = -1;
    char hasPiece = FALSE;
    while (1)
    {
        int key = gfx_pollkey();
        if (key == '0')
            break;

        if (!hasPiece)
        {
            insertNextPiece(&model, xoffset);
            chooseNextPiece(&model, &xoffset);
            hasPiece = TRUE;
        }

        if (key == SDLK_LEFT)
        {
            moveDir = LEFT;
        }

        else if (key == SDLK_RIGHT)
        {
            moveDir = RIGHT;
        }

        else if (key == SDLK_DOWN)
        {
            while (willCrossBoundaries(&model, DOWN) != GROUND_TOUCH &&
                   collisionCheck(&model, DOWN) != GROUND_TOUCH)
            {
                movePiece(&model, DOWN);
            }
            collidePiece(&model);
            hasPiece = FALSE;
        }

        if (key == SDLK_SPACE)
        {
            rotatePiece();
        }

        if (counter++ == 20)
        {
            moveDir = DOWN;
            counter = 0;
        }

        char boundsCrossType = willCrossBoundaries(&model, moveDir);
        char collisionType = collisionCheck(&model, moveDir);
        if (boundsCrossType == GROUND_TOUCH || collisionType == GROUND_TOUCH)
        {
            collidePiece(&model);
            hasPiece = FALSE;
        }

        if (boundsCrossType == FALSE && collisionType == FALSE)
            movePiece(&model, moveDir);

        moveDir = -1;

        clearScreen();
        drawBoard(model);
        gfx_updateScreen();
        SDL_Delay(FRAMERATE_DELAY);
    }
    return 0;
}
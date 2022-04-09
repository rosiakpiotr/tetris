#include "include/primlib.h"
#include "include/types.h"
#include "include/controller.h"
#include "include/view.h"
#include "include/piece_definition.h"

#include <time.h>
#include <stdlib.h>

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

    // Random int between 0 and 6
    int pieceI = rand() % 7;
    int rotStage = rand() % 4;

    int x, y;
    findRotationAxisForPiece(pieces[pieceI][rotStage], &x, &y);
    insertPiece(&model, pieceI, x, y, rotStage);
    printf("%d, rot: %d\n", pieceI, rotStage);

    int counter = 0;
    EDirection moveDir = -1;
    while (1)
    {
        int key = gfx_pollkey();
        if (key == '0')
            break;

        if (key == SDLK_LEFT)
        {
            moveDir = LEFT;
        }

        else if (key == SDLK_RIGHT)
        {
            moveDir = RIGHT;
        }

        else if (key == SDLK_SPACE)
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
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

    int counter = 0;
    while (1)
    {
        int key = gfx_pollkey();
        if (key == '0')
            break;

        if (key == SDLK_SPACE)
        {
            rotatePiece();
        }

        clearScreen();
        drawBoard(model);
        gfx_updateScreen();
        SDL_Delay(FRAMERATE_DELAY);
    }
    return 0;
}
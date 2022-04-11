#include "raylib.h"
#include "defaults.h"
#include "game.h"
#include "types.h"

void checkGameState(struct Player* player, struct EnemyArray* enemies)
{
    if (enemies->length == 0)
        DrawText("---You Win!---", SCR_WIDTH/2 - 50, SCR_HEIGHT/2, 25, GREEN);
    else if(player->lives == 0)
        DrawText("---Game Over---", SCR_WIDTH/2 - 50, SCR_HEIGHT/2 - 50, 25, YELLOW);
}

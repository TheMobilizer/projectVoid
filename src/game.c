#include "raylib.h"
#include "defaults.h"
#include "game.h"
#include "types.h"
#include "collections.h"
#include <stdlib.h>

void checkGameState(struct Player* player, struct EnemyArray* enemies)
{
    if (enemies->length == 0)
        DrawText("---You Win!---", SCR_WIDTH/2 - 50, SCR_HEIGHT/2, 25, GREEN);
    else if(player->lives == 0)
        DrawText("---Game Over---", SCR_WIDTH/2 - 50, SCR_HEIGHT/2 - 50, 25, YELLOW);
}

struct Level *buildLevel()
{
    struct Level *level = (struct Level*)malloc(sizeof(struct Level));
    level->enemyWaves = (struct EnemyArray*)malloc(sizeof(struct EnemyArray)*2);
    EnemyArray_populate(level->enemyWaves, "dat/em1.enmap", 10, 10, 20);
    //EnemyArray_populate((level->enemyWaves + 1), "dat/em2.enmap", 10, 10, 20);
    return level;
}

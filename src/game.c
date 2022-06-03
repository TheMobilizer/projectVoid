#include "raylib.h"
#include "include/defaults.h"
#include "include/game.h"
#include "include/types.h"
#include "include/collections.h"
#include <stdlib.h>

void checkGameState(struct Player* player, struct Level* level)
{
    if (((level->enemyWaves + level->currentWave - 1)->length == 0) && (level->currentWave == level->maxWaves))
        DrawText("---You Win!---", SCR_WIDTH/2 - 50, SCR_HEIGHT/2, 25, GREEN);
    else if(player->lives == 0)
        DrawText("---Game Over---", SCR_WIDTH/2 - 50, SCR_HEIGHT/2 - 50, 25, YELLOW);
}

struct Level *buildLevel()
{
    struct Level *level = (struct Level*)malloc(sizeof(struct Level));
    
    level->enemyWaves = createEnemyArray();
    level->numEnArr = 0;
    level->currentWave = 1;
    level->maxWaves = 3;
    level->timeElapsed = 0.0f;
    //EnemyArray_populate((level->enemyWaves), "dat/em1.enmap", 10, 10, 20);
    //EnemyArray_populate((level->enemyWaves + 1), "dat/em2.enmap", 10, 10, 20);
    level = addEnemyWave(level, "dat/em1.enmap");
    level = addEnemyWave(level, "dat/em2.enmap");
    level = addEnemyWave(level, "dat/em3.enmap");
    return level;
}

struct Level *addEnemyWave(struct Level *level, char *waveFilePath)
{
    EnemyArray_populate((level->enemyWaves + level->numEnArr), waveFilePath, 10, 10, 20);
    (level->numEnArr)++;
    level->enemyWaves = (struct EnemyArray *)realloc(level->enemyWaves, (level->numEnArr + 1) * sizeof(struct EnemyArray));
    
    level->enemyWaves[level->numEnArr] = *(createEnemyArray());
    return level;
}

void Level_update(struct Level *level, struct Player *player, float dt)
{
    
    if(((level->enemyWaves + level->currentWave - 1)->length <= 0) && (!(level->currentWave >= level->maxWaves)))
    {
        level->timeElapsed += dt;
        if((level->timeElapsed >= 2.0f) && (level->timeElapsed <=4.0f))
        {
            DrawText("Next Wave Incoming!", (float)(SCR_WIDTH/2 - 50), (float)(SCR_HEIGHT/2), 20, RED);
        }
        if(level->timeElapsed >= 6.0f)
        {
            (level->currentWave)++;
            level->timeElapsed = 0.0f;
        }
        
    }
    EnemyArray_update((level->enemyWaves + level->currentWave -1), player, dt);
    
}

void Level_draw(struct Level *level)
{
    EnemyArray_draw((level->enemyWaves + level->currentWave -1));
}

void Level_free(struct Level *level)
{
    free(level->enemyWaves->enemies);
    free(level->enemyWaves);
    free(level);
}

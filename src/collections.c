#ifndef INCLUDED

#include "raylib.h"
#include "actors.h"
#include "defaults.h"

#define INCLUDED
#endif

#include "collections.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

struct EnemyArray *createEnemyArray()
{
    struct EnemyArray *enemyArray = (struct EnemyArray*)malloc(sizeof(struct EnemyArray));
    enemyArray->enemies =(struct Enemy*)malloc(sizeof(struct Enemy));
    enemyArray->length = 0;
    return enemyArray;
}

struct EnemyArray *addEnemy(struct EnemyArray* enemyArray, struct Enemy* enemy)
{
    enemyArray->enemies[enemyArray->length] = *enemy;
    (enemyArray->length)++;
    //printf("In addEnemy()\n");
    enemyArray->enemies = (struct Enemy*)realloc(enemyArray->enemies,(enemyArray->length + 1)*sizeof(struct Enemy));
    return enemyArray;
}

void EnemyArray_populate(struct EnemyArray* enemyArray, char *filePath, int x, int y, int padding)
{
    FILE *waveFile;
    char c;
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
       printf("Current working dir: %s\n", cwd);
   }
    printf("Populating EnemyArray. filePath: \"%s\" \n",filePath);
    if((waveFile = fopen(filePath, "r")) == NULL)
        printf("Unable to open file\n");
    else
    {
        int xp = x;
        int yp = y;
        printf("File opened successfully\n");
        while((c = fgetc(waveFile)) != EOF)
        {
            if (c == 'E')
            {
                
                enemyArray = addEnemy(enemyArray, createEnemy((float) (xp /*+ (xp == x?0:20)*/), (float) yp, 20, 20, BLUE,"Blue-Swarm Member"));
                xp+=20;
               
            }
            else if(c == '\n')
            {
                yp+= padding;
                xp = x;
            }
            else
                xp+=padding;
        }
    }
    
    fclose(waveFile);
}

void EnemyArray_draw(struct EnemyArray* enemyArray)
{
    int i;
    for (i = 0; i < enemyArray->length; i++)
        Enemy_draw((enemyArray->enemies + i));
}

void EnemyArray_update(struct EnemyArray* enemyArray)
{
    int i;
    for (i = 0; i < enemyArray->length; i++)
        Enemy_update((enemyArray->enemies + i));
}

void EnemyArray_free(struct EnemyArray* enemyArray)
{
    free(enemyArray->enemies);
    free(enemyArray);
}


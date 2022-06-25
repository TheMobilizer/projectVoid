#include "raylib.h"
#include "include/actors.h"
#include "include/defaults.h"
#include "include/collections.h"

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
    printf("In addEnemy()\n");
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
            if (c == 'B')
            {
                //printf("c == B\n");
                addEnemy(enemyArray, createEnemy((float) (xp), (float) yp, ES_HEIGHT, ES_WIDTH, BLUE,"Blue-Swarm Member", Enemy_updateCos,ES_RIGHT));
                xp += ES_WIDTH + padding;
               
            }
            else if (c == 'G')
            {
                //printf("c == G\n");
                addEnemy(enemyArray, createEnemy((float) (xp), (float) yp, ES_HEIGHT, ES_WIDTH, GREEN,"Green-Swarm Member", Enemy_updateSin, ES_RIGHT));
                xp += ES_WIDTH + padding;
               
            }
            else if (c == 'R')
            {
                //printf("c == R\n");
                addEnemy(enemyArray, createEnemy((float) (xp), (float) yp, ES_HEIGHT, ES_WIDTH, RED,"Red-Swarm Member", Enemy_updateSeek, ES_RIGHT));
                xp += ES_WIDTH + padding;
               
            }
            else if(c == '\n')
            {
                yp+= ES_HEIGHT + padding;
                xp = x;
            }
            else
                xp+= ES_WIDTH + padding;
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

void EnemyArray_update(struct EnemyArray* enemyArray, struct Player* player, float dt)
{
    int i;
    for (i = 0; i < enemyArray->length; i++)
    {
        //printf("Updating enemy %d\n", i);
        (enemyArray->enemies + i)->update((enemyArray->enemies + i), player, dt);
        if (Enemy_collide((enemyArray->enemies + i), player))
        {
            EnemyArray_destroyEnemy(enemyArray, i);
            printf("In EnemyArray_update(). Enemy destroyed. EnemyArray->length = %d\n", enemyArray->length);
        }
    }
}

void EnemyArray_destroyEnemy(struct EnemyArray* enemyArray, int index)
{
    struct Enemy tempEnemy = enemyArray->enemies[enemyArray->length - 1];
    enemyArray->enemies[enemyArray->length - 1] = enemyArray->enemies[index];
    enemyArray->enemies[index] = tempEnemy;
    enemyArray->length--;
}


void EnemyArray_free(struct EnemyArray* enemyArray)
{
    free(enemyArray->enemies);
    free(enemyArray);
}

//------------------------------------------------------------------------------

//------------------------Bullet Array functions--------------------------------

struct BulletArray *createBulletArray()
{
    struct BulletArray *bulletArray = (struct BulletArray*)malloc(sizeof(struct BulletArray));
    bulletArray->bullets =(struct Bullet*)malloc(sizeof(struct Bullet));
    bulletArray->length = 0;
    return bulletArray;
}

struct BulletArray *addBullet(struct BulletArray* bulletArray, struct Bullet* bullet)
{
    bulletArray->bullets[bulletArray->length] = *bullet;
    (bulletArray->length)++;
    //printf("In addEnemy()\n");
    bulletArray->bullets = (struct Bullet*)realloc(bulletArray->bullets,(bulletArray->length + 1)*sizeof(struct Bullet));
    return bulletArray;
}

void BulletArray_draw(struct BulletArray* bulletArray)
{
    int i;
    for (i = 0; i < bulletArray->length; i++)
        Bullet_draw((bulletArray->bullets + i));
}

void BulletArray_update(struct BulletArray* bulletArray, float dt)
{
    int i;
    for (i = 0; i < bulletArray->length; i++)
    {
        if (bulletArray->bullets[i].position.y < -bulletArray->bullets[i].colRec.height)
            BulletArray_destroyBullet(bulletArray, i);
        Bullet_update((bulletArray->bullets + i), dt);
    }
}

void BulletArray_destroyBullet(struct BulletArray* bulletArray, int index)
{
    struct Bullet tempBullet = bulletArray->bullets[bulletArray->length - 1];
    bulletArray->bullets[bulletArray->length - 1] = bulletArray->bullets[index];
    bulletArray->bullets[index] = tempBullet;
    bulletArray->length--;
}

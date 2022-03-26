#ifndef INCLUDED

#include "raylib.h"
#include "actors.h"
#include "defaults.h"

#define INCLUDED
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//--------------------------Player functions-------------------------------

struct Player* createPlayer(float x, float y, float height, float width, Color color)
{
    struct Player *player = (struct Player *)malloc(sizeof(struct Player));
    
    player->position.x = x;
    player->position.y = y;
    
    player->colRec.x = x;
    player->colRec.y = y;
    
    player->colRec.height = height;
    player->colRec.width = width;
    
    player->color = color;
    
    player->up = FALSE;
    player->down = FALSE;
    player->right = FALSE;
    player->left = FALSE;
    
    player->velocity.x = 5;
    player->velocity.y = 5;
    
    return player;
}

void Player_setPosition(struct Player *player, float x, float y)
{
    player->position.x = x;
    player->position.y = y;
    player->colRec.x = x;
    player->colRec.y = y;
}

void Player_draw(struct Player *player)
{
    DrawRectangleRec(player->colRec, player->color);    
}

void Player_update(struct Player *player)
{

    player->up = IsKeyDown(KEY_UP);
    player->down = IsKeyDown(KEY_DOWN);
    player->right = IsKeyDown(KEY_RIGHT);
    player->left = IsKeyDown(KEY_LEFT);

    if(player->up)
    {
        player->velocity.y = -Y_VEL;
        printf("player up\n");
    }
    
    else if(player->down)
    {
        player->velocity.y = Y_VEL;
        printf("player down\n");
    }
    
    if (player->right)
    {
        player->velocity.x = X_VEL;
        printf("player right\n");
    }
    else if(player->left)
    {
        player->velocity.x = -X_VEL;
        printf("player left\n");
    }
    
    Player_setPosition(player ,player->position.x + player->velocity.x, player->position.y + player->velocity.y);
   
    player->velocity.x = 0;
    player->velocity.y = 0;
    
}

void Player_free(struct Player *player)
{
    free(player);
}

//--------------------------------------------------------------------------

//--------------------------Enemy functions---------------------------------

void Enemy_setPosition(struct Enemy *enemy, float x, float y)
{
    enemy->position.x = x;
    enemy->position.y = y;
    enemy->colRec.x = x;
    enemy->colRec.y = y;
}

void Enemy_setSize(struct Enemy *enemy, float height, float width)
{
    enemy->colRec.height = height;
    enemy->colRec.width = width;
}

void Enemy_setPosCentre(struct Enemy *enemy, float x, float y)
{
    Enemy_setPosition(enemy, x-((enemy->colRec.width)/2),y-((enemy->colRec.height)/2));
}

struct Enemy* createEnemy(float x, float y, float height, float width, Color color, char* type, char* dir)
{
    struct Enemy *enemy = (struct Enemy *)malloc(sizeof(struct Enemy));
    
    Enemy_setSize(enemy, height, width);
    Enemy_setPosCentre(enemy, x, y);
    
    enemy->color = color;
    enemy->type = type;
    
    if(strcmp(dir, "UP") == 0)
    {
        enemy->up = TRUE;
        enemy->down = FALSE;
        enemy->right = FALSE;
        enemy->left = FALSE;
        printf("Enemy direction is UP\n");
    }
    else if(strcmp(dir, "DOWN") == 0)
    {
        enemy->up = FALSE;
        enemy->down = TRUE;
        enemy->right = FALSE;
        enemy->left = FALSE;
        printf("Enemy direction is DOWN\n");
    }
    else if(strcmp(dir, "RIGHT") == 0)
    {
        enemy->up = FALSE;
        enemy->down = FALSE;
        enemy->right = TRUE;
        enemy->left = FALSE;
        printf("Enemy direction is RIGHT and dir = %s\n", dir);
    }
    else if(strcmp(dir, "LEFT") == 0)
    {
        enemy->up = FALSE;
        enemy->down = FALSE;
        enemy->right = FALSE;
        enemy->left = TRUE;
        printf("Enemy direction is LEFT and dir = %s\n", dir);
    }
    return enemy;
    
}

void Enemy_draw(struct Enemy *enemy)
{
    DrawRectangleRec(enemy->colRec, enemy->color);
}

void Enemy_update(struct Enemy *enemy)
{
    //int right = TRUE;
    
    if(enemy->right)
    {
        if((enemy->position.x + ES_WIDTH) > SCR_WIDTH)
        {
            enemy->right = FALSE;
            enemy->left = TRUE;
            enemy->position.y += 20;
        }
        else
            Enemy_setPosition(enemy, enemy->position.x+2, enemy->position.y);
    }
    else if(enemy->left)
    {
        if((enemy->position.x) < 0)
        {
            enemy->right = TRUE;
            enemy->left = FALSE;
            enemy->position.y += 20;
        }
        else
            Enemy_setPosition(enemy, enemy->position.x-2, enemy->position.y);
    }
    
    //printf("In Enemy_update()\n");
}

void Enemy_free(struct Enemy *enemy)
{
    free(enemy);
}

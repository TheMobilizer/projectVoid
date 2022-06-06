#include "raylib.h"
#include "include/actors.h"
#include "include/defaults.h"
#include "include/misc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    
    player->lives = 10;
    player->isAlive = TRUE;
    player->fire = FALSE;
    player->currentBulletSet = createBulletArray();
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
    //if(player->currentBullet != NULL)
        BulletArray_draw(player->currentBulletSet);
}

void Player_update(struct Player *player, struct Level *level, float dt)
{
    if(player->isAlive)
    {
        if (player->lives == 0)
        {
            player->isAlive = FALSE;
            //Player_free(player);
            printf("Player is dead. Game over.");
            
            return;
        }
        
        Player_collide(player, level);
        
        player->up = IsKeyDown(KEY_UP);
        player->down = IsKeyDown(KEY_DOWN);
        player->right = IsKeyDown(KEY_RIGHT);
        player->left = IsKeyDown(KEY_LEFT);
        player->fire = IsKeyDown(KEY_Z);
        
        
        if(player->position.x + player->colRec.width >= SCR_WIDTH)
            Player_setPosition(player,SCR_WIDTH - player->colRec.width - 1, player->position.y);
        else if(player->position.x <= 0)
            Player_setPosition(player, 1, player->position.y);
        if(player->position.y <= 0)
            Player_setPosition(player, player->position.x,1);
        else if(player->position.y + player->colRec.height >= SCR_HEIGHT)
            Player_setPosition(player, player->position.x, SCR_HEIGHT - player->colRec.height - 1);
            
        if(player->up)
        {
            player->velocity.y = -dt*Y_VEL;
        }
    
        else if(player->down)
        {
            player->velocity.y = dt*Y_VEL;
        }
    
        if (player->right)
        {
            player->velocity.x = dt*X_VEL;
        }
        else if(player->left)
        {
            player->velocity.x = -dt*X_VEL;
        }
    
        Player_setPosition(player ,player->position.x + player->velocity.x, player->position.y + player->velocity.y);
        
        if(player->fire)
        {
            if(player->position.y - player->currentBulletSet->bullets[player->currentBulletSet->length - 1].position.y >= 100)
                player->currentBulletSet = addBullet(player->currentBulletSet,createBullet(player->position.x + 10, player->position.y, 10, 5, RAYWHITE, "Simple Bullet", ES_UP));
        }
        
        //if(player->currentBulletSet != NULL)
        //{
            BulletArray_update(player->currentBulletSet, dt);
        //}
   
        player->velocity.x = 0;
        player->velocity.y = 0;
    }
    else
    {
        player->color = RAYWHITE;
    }
}

void Player_die(struct Player *player)
{
    player->lives--;
    player->color = RAYWHITE;
}

void Player_free(struct Player *player)
{
    free(player);
}

void Player_collide(struct Player *player, struct Level *level)
{
    int i;
    for(i = 0; i < (level->enemyWaves + level->currentWave - 1)->length; i++)
    {
        if(CheckCollisionRecs(player->colRec, (level->enemyWaves + level->currentWave - 1)->enemies[i].colRec))
        {
            Player_die(player);
            EnemyArray_destroyEnemy((level->enemyWaves + level->currentWave - 1), i);
            printf("In Player_collide(). enemyArray->length = %d\n",(level->enemyWaves + level->currentWave - 1)->length);
            break;
        }
        else
            player->color = MAGENTA;
    }
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

struct Enemy* createEnemy(float x, float y, float height, float width, Color color, char* type, void (*updateFunction)(struct Enemy *, struct Player *, float),int right, int left, int up, int down)
{
    struct Enemy *enemy = (struct Enemy *)malloc(sizeof(struct Enemy));
    
    Enemy_setSize(enemy, height, width);
    Enemy_setPosCentre(enemy, x, y);
    
    enemy->color = color;
    enemy->type = type;
    
    enemy->up = up;
    enemy->down = down;
    enemy->right = right;
    enemy->left = left;
    
    enemy->isAlive = true;
    enemy->timeElapsed = 0.0f;
    enemy->totalTime = 0.0f;
    enemy->trig_x = 50.0f;
    enemy->update = updateFunction;
    return enemy;
    
}

void Enemy_draw(struct Enemy *enemy)
{
    DrawRectangleRec(enemy->colRec, enemy->color);
}

void Enemy_update(struct Enemy *enemy, struct Player *player, float dt)
{
    enemy->totalTime+=dt;
    if(enemy->totalTime >= 5.0f)
    {
        enemy->totalTime = 0;
        //if(enemy->color != BLACK)
            //enemy->color = BLACK;
        //else
          //  enemy->color = BLUE;
    }
    if((enemy->position.x + ES_WIDTH) > SCR_WIDTH)
    {
        enemy->right = FALSE;
        enemy->left = TRUE;
        if (enemy->down)
            enemy->position.y += 20;
        else if(enemy->up)
            enemy->position.y -= 20;
    }
    else if((enemy->position.x) < 0)
    {
        enemy->right = TRUE;
        enemy->left = FALSE;
        if (enemy->down)
            enemy->position.y += 20;
        else if(enemy->up)
            enemy->position.y -= 20;
    }
    if((enemy->position.y) > SCR_HEIGHT)
    {
        printf("Enemy below screen\n");
        if(!(enemy->up))
            enemy->position.y = -2*ES_HEIGHT;
    }
    else if((enemy->position.y + ES_WIDTH) < 0)
    {
        printf("Enemy above screen\n");
        if(!(enemy->down))
            enemy->position.y = SCR_HEIGHT + ES_HEIGHT ;
    }
    
    if(enemy->right)
    {

        if((enemy->position.x + ES_WIDTH) > SCR_WIDTH)
        {
            enemy->right = FALSE;
            enemy->left = TRUE;
        }
        
        Enemy_setPosition(enemy, enemy->position.x+(dt*ES_X_VEL), enemy->position.y);
    }
    else if(enemy->left)
    {
        if((enemy->position.x) < 0)
        {
            enemy->right = TRUE;
            enemy->left = FALSE;
        }
        
        Enemy_setPosition(enemy, enemy->position.x-(dt*ES_X_VEL), enemy->position.y);
    }
    
    if(enemy->down)
    {
        if((enemy->position.y) > SCR_HEIGHT)
        {
            Enemy_setPosition(enemy, enemy->position.x, -2*ES_HEIGHT);
        }
        
        Enemy_setPosition(enemy, enemy->position.x, enemy->position.y+2);
    }
    else if(enemy->up)
    {
        if((enemy->position.y + 20) < 0)
        {
            Enemy_setPosition(enemy, enemy->position.x, SCR_HEIGHT + ES_HEIGHT);
        }
            
        Enemy_setPosition(enemy, enemy->position.x, enemy->position.y-2);
    }
}

void Enemy_updateSeek(struct Enemy *enemy, struct Player *player, float dt)
{
    enemy->timeElapsed += dt;
    float difX = player->position.x - enemy->position.x;
    float difY = player->position.y - enemy->position.y;
    Vector2 direction = {(difX)/sqrt(pow(difX, 2) + pow(difY, 2)),(difY)/sqrt(pow(difX, 2) + pow(difY, 2))};
    if(enemy->timeElapsed >= 2.0f)
        Enemy_setPosition(enemy, enemy->position.x+(direction.x*dt*ES_SEEK_X_VEL), enemy->position.y+(direction.y*dt*ES_SEEK_Y_VEL));
    else
        Enemy_update(enemy, player, dt);
    
}

void Enemy_updateSin(struct Enemy *enemy, struct Player *player, float dt)
{
    
    enemy->timeElapsed += dt;
    enemy->trig_x += ES_X_VEL*dt;
    if (enemy->trig_x >= SCR_WIDTH/5)
        enemy->trig_x = 0.0f;
    if(enemy->right)
    {
        if(enemy->position.x < 0)
            Enemy_setPosition(enemy, 0, enemy->position.y);
        printf("Right: delta enemy->position.x = %lf\n", ES_X_VEL*dt);
        Enemy_setPosition(enemy, (enemy->position.x + (ES_X_VEL*dt)), (enemy->position.y + (sin(map(enemy->trig_x, 0, SCR_WIDTH/5, 0, 2*M_PI)))));
        if(enemy->position.x + ES_WIDTH >= SCR_WIDTH)
        {
            enemy->right = FALSE;
            enemy->left = TRUE;
        }
    }
    if(enemy->left)
    {
        printf("Left: delta enemy->position.x = %lf\n", ES_X_VEL*dt);
        Enemy_setPosition(enemy, (enemy->position.x - (ES_X_VEL*dt)), (enemy->position.y+(sin(map(enemy->trig_x, 0, SCR_WIDTH/5, 0, 2*M_PI)))));
        if(enemy->position.x <= 0)
        {
            enemy->right = TRUE;
            enemy->left = FALSE;
        }
    }
    if(enemy->position.y > SCR_HEIGHT)
        Enemy_setPosition(enemy, enemy->position.x, -20);
    
    
}

void Enemy_destroy(struct Enemy *enemy)
{
    enemy->isAlive = false;
    Enemy_free(enemy);
}

void Enemy_free(struct Enemy *enemy)
{
    free(enemy);
}

int Enemy_collide(struct Enemy *enemy, struct Player *player)
{
    for(int i = 0; i <player->currentBulletSet->length; i++)
    {
        if (CheckCollisionRecs(enemy->colRec, (player->currentBulletSet->bullets[i].colRec)))
        {
            BulletArray_destroyBullet(player->currentBulletSet, i);
            return 1;
        }
    }
    return 0;
}
//------------------------------------------------------------------

//--------------Player Bullet struct and functions------------------

struct Bullet* createBullet(float x, float y, float height, float width, Color color, char* type, int right, int left, int up, int down)
{
    struct Bullet *bullet = (struct Bullet *)malloc(sizeof(struct Bullet));
    bullet->position.x = x;
    bullet->position.y = y;
    bullet->colRec.x = x;
    bullet->colRec.y = y;
    bullet->color = color;
    bullet->colRec.width = width;
    bullet->colRec.height = height;
    bullet->type = type;
    bullet->right = right;
    bullet->left = left;
    bullet->up = up;
    bullet->down = down;
    return bullet;
}
void Bullet_setPosition(struct Bullet *bullet, float x, float y)
{
    bullet->position.x = x;
    bullet->position.y = y;
    bullet->colRec.x = x;
    bullet->colRec.y = y;
}

void Bullet_update(struct Bullet *bullet, float dt)
{
    if(bullet->position.y < -10)
    {
        bullet = NULL;
        return;
    }
    Bullet_setPosition(bullet, bullet->position.x, bullet->position.y-(dt * SIMPLE_BULLETS_VELY));
    
}
void Bullet_draw(struct Bullet *bullet)
{
    DrawRectangleRec(bullet->colRec, bullet->color);
}

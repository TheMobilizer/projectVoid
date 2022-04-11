#ifndef ACTORS_H
#define ACTORS_H

#include "actors.h"
#include "collections.h"

//-------------------------Player functions-------------------------

struct Player* createPlayer(float x, float y, float height, float width, Color color);

void Player_setPosition(struct Player *player, float x, float y);
void Player_draw(struct Player *player);
void Player_update(struct Player *player, struct EnemyArray *enemyArray);
void Player_free(struct Player *player);
void Player_collide(struct Player *player, struct EnemyArray *enemyArray);

//--------------------------Enemy functions-------------------------



void Enemy_setPosition(struct Enemy *enemy, float x, float y);
void Enemy_setSize(struct Enemy *enemy, float height, float width);
void Enemy_setPosCentre(struct Enemy *enemy, float x, float y);

struct Enemy* createEnemy(float x, float y, float height, float width, Color color, char* type, int right, int left, int up, int down);

void Enemy_draw(struct Enemy *enemy);
void Enemy_update(struct Enemy *enemy, struct Player* player);
void Enemy_destroy(struct Enemy *enemy);
void Enemy_free(struct Enemy *enemy);


//----------------------------------Player Bullet functions----------------------------

struct Bullet* createBullet(float x, float y, float height, float width, Color color, char* type, int right, int left, int up, int down);

void Bullet_draw(struct Bullet *bullet);
void Bullet_update(struct Bullet *bullet);
void Bullet_setPosition(struct Bullet *bullet, float x, float y);
void Bullet_destroy(struct Bullet *bullet);
void Bullet_free(struct Bullet *bullet);

#endif

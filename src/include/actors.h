#ifndef ACTORS_H
#define ACTORS_H

#include "collections.h"

//-------------------------Player functions-------------------------

struct Player* createPlayer(float x, float y, float height, float width, Color color);

void Player_setPosition(struct Player *player, float x, float y);
void Player_draw(struct Player *player);
void Player_update(struct Player *player, struct Level *level, float dt);
void Player_free(struct Player *player);
void Player_collide(struct Player *player, struct Level *level);

//--------------------------Enemy functions-------------------------



void Enemy_setPosition(struct Enemy *enemy, float x, float y);
void Enemy_setSize(struct Enemy *enemy, float height, float width);
void Enemy_setPosCentre(struct Enemy *enemy, float x, float y);

struct Enemy* createEnemy(float x, float y, float height, float width, Color color, char* type, void (*updateFunction)(struct Enemy *, struct Player *, float), int right, int left, int up, int down);

void Enemy_draw(struct Enemy *enemy);
void Enemy_update(struct Enemy *enemy, struct Player *player, float dt);
void Enemy_updateSeek(struct Enemy *enemy, struct Player *player, float dt);
void Enemy_updateSin(struct Enemy *enemy, struct Player *player, float dt);
void Enemy_updateCos(struct Enemy *enemy, struct Player *player, float dt);
void Enemy_destroy(struct Enemy *enemy);
void Enemy_free(struct Enemy *enemy);
int Enemy_collide(struct Enemy *enemy, struct Player *player);


//----------------------------------Player Bullet functions----------------------------

struct Bullet* createBullet(float x, float y, float height, float width, Color color, char* type, int right, int left, int up, int down);

void Bullet_draw(struct Bullet *bullet);
void Bullet_update(struct Bullet *bullet, float dt);
void Bullet_setPosition(struct Bullet *bullet, float x, float y);
void Bullet_destroy(struct Bullet *bullet);
void Bullet_free(struct Bullet *bullet);

#endif

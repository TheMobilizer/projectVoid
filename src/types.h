#ifndef TYPES_H
#define TYPES_H

#include "raylib.h"

struct Bullet
{
    Vector2 position;
    Vector2 velocity;
    Rectangle colRec;
    Color color;
    char* type;
    int up;
    int down;
    int right;
    int left;
    bool isAlive;
};

struct Enemy
{
    Vector2 position;
    Vector2 velocity;
    Rectangle colRec;
    Color color;
    int up;
    int down;
    int right;
    int left;
    char* type;
    bool isAlive;
};

struct Player
{
    Vector2 position;
    Vector2 velocity;
    Rectangle colRec;
    Color color;
    struct BulletArray *currentBulletSet;
    int lives;
    int isAlive;
    int fire;
    int up;
    int down;
    int right;
    int left;
};

struct EnemyArray
{
    struct Enemy *enemies;
    int length;
};

struct BulletArray
{
    struct Bullet *bullets;
    int length;
};

#endif

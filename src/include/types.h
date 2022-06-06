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
    bool up;
    bool down;
    bool right;
    bool left;
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
    bool isAlive;
    bool fire;
    bool up;
    bool down;
    bool right;
    bool left;
};

struct Enemy
{
    Vector2 position;
    Vector2 velocity;
    Rectangle colRec;
    Color color;
    bool up;
    bool down;
    bool right;
    bool left;
    char* type;
    bool isAlive;
    float timeElapsed;
    float totalTime;
    float trig_x;
    void (*update)(struct Enemy *, struct Player *, float);
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

struct Level
{
    struct EnemyArray *enemyWaves;
    int numEnArr;
    int currentWave;
    int maxWaves;
    float timeElapsed;
};

#endif

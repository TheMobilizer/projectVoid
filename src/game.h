#ifndef GAME_H
#define GAME_H

#include "types.h"


void checkGameState(struct Player* player, struct Level *level);

struct Level *buildLevel();
struct Level *addEnemyWave(struct Level *level, char *waveFilePath);
void Level_draw(struct Level *level);
void Level_update(struct Level *level, struct Player* player, float dt);
#endif

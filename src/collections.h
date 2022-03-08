struct EnemyArray
{
    struct Enemy *enemies;
    int length;
};

struct EnemyArray *createEnemyArray();
struct EnemyArray *addEnemy(struct EnemyArray* enemyArray, struct Enemy* enemy);
void EnemyArray_populate(struct EnemyArray* enemyArray, char *filePath, int x, int y, int padding);
void EnemyArray_draw(struct EnemyArray* enemyArray);
void EnemyArray_update(struct EnemyArray* enemyArray);
void EnemyArray_free(struct EnemyArray* enemyArray);

void drawAll();
void updateAll();
void freeAll();

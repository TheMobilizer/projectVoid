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
void EnemyArray_destroyEnemy(struct EnemyArray* enemyArray, int index);

struct BulletArray
{
    struct Bullet *bullets;
    int length;
};

struct BulletArray *createBulletArray();
struct BulletArray *addBullet(struct BulletArray* bulletArray, struct Bullet* bullet);
//void EnemyArray_populate(struct EnemyArray* enemyArray, char *filePath, int x, int y, int padding);
void BulletArray_draw(struct BulletArray* bulletArray);
void BulletArray_update(struct BulletArray* bulletArray);
void BulletArray_free(struct BulletArray* bulletArray);
void BulletArray_destroyBullet(struct BulletArray* BulletArray, int index);


void drawAll();
void updateAll();
void freeAll();

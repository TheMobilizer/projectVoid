
//-------------------------Player struct and functions-------------------------

struct Player
{
    Vector2 position;
    Vector2 velocity;
    Rectangle colRec;
    Color color;
    int up;
    int down;
    int right;
    int left;
};

struct Player* createPlayer(float x, float y, float height, float width, Color color);

void Player_setPosition(struct Player *player, float x, float y);
void Player_draw(struct Player *player);
void Player_update(struct Player *player);
void Player_free(struct Player *player);

//-----------------------------------------------------------------------------

//--------------------------Enemy struct and functions-------------------------

struct Enemy
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
};

void Enemy_setPosition(struct Enemy *enemy, float x, float y);
void Enemy_setSize(struct Enemy *enemy, float height, float width);
void Enemy_setPosCentre(struct Enemy *enemy, float x, float y);

struct Enemy* createEnemy(float x, float y, float height, float width, Color color, char* type, int right, int left, int up, int down);

void Enemy_draw(struct Enemy *enemy);
void Enemy_update(struct Enemy *enemy);
void Enemy_free(struct Enemy *enemy);

void Enemy_drawAll(struct Enemy **enemies);

//-----------------------------------------------------------------------------

//---------------------------Group functions------------------------------


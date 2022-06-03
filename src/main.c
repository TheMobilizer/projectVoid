#include "raylib.h"
#include "include/actors.h"
#include "include/defaults.h"
#include "include/collections.h"
#include "include/types.h"
#include "include/game.h"

#include <stdio.h>

int main(void)
{
    float dt = 0.0f;    
    struct Player *mainPlayer = createPlayer((float) SCR_WIDTH/2,(float) 550,20,20, MAGENTA);
    
    struct Level *level1 = buildLevel();
    //struct EnemyArray *enemyGroup = createEnemyArray();
    //EnemyArray_populate(enemyGroup, "dat/em1.enmap", 10, 10, 20);
    
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "raylib [core] example - basic window");
    //ToggleFullscreen();
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        dt = GetFrameTime();
        //time_elapsed += dt;
        //printf("Last Frame Time: %lfs\n", dt);
        //printf("Time Elapsed: %lfs\n", GetTime());
        Player_update(mainPlayer, level1, dt);
        Level_update(level1, mainPlayer, dt);
        //printf("x: %lf\n",(anEnemy->position).x);
        //printf("y: %lf\n",(anEnemy->position).y);
        //printf("enemy type: %s\n", anEnemy->type);
        
        //printf("x: %lf\n", ((enemyGroup->enemies + 1)->position.x));
        //printf("y: %lf\n", ((enemyGroup->enemies + 1)->position.y));
        //printf("enemy type: %s\n", anEnemy->type);
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            DrawFPS(10,10);
            DrawText("Player Color", 10, 30, 14, mainPlayer->color);
            
            //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            Player_draw(mainPlayer);
            //EnemyArray_draw(level1->enemyWaves);
            Level_draw(level1);
            
        EndDrawing();
        
        checkGameState(mainPlayer, level1);
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    Player_free(mainPlayer);
    EnemyArray_free(level1->enemyWaves);
    CloseWindow();
    return 0;
}

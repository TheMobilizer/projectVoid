#ifndef INCLUDED
#include "raylib.h"
#include "actors.h"
#include "defaults.h"
#define INCLUDED
#endif
#include <stdio.h>
#include "collections.h"

int main(void)
{
    
    struct Player *mainPlayer = createPlayer((float) SCR_WIDTH/2,(float) 550,20,20, MAGENTA);
    
    
    struct EnemyArray *enemyGroup = createEnemyArray();
    EnemyArray_populate(enemyGroup, "dat/em1.enmap", 50, 50, 20);
    
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "raylib [core] example - basic window");
    //ToggleFullscreen();
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        
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

            //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            Player_update(mainPlayer);
            Player_draw(mainPlayer);
            
            EnemyArray_update(enemyGroup);
            
            
            EnemyArray_draw(enemyGroup);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    Player_free(mainPlayer);
    EnemyArray_free(enemyGroup);
    CloseWindow();    
    return 0;
}

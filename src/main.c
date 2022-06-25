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
    
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "raylib [core] example - basic window");
    //ToggleFullscreen();
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        dt = GetFrameTime();
        
        Player_update(mainPlayer, level1, dt);
        Level_update(level1, mainPlayer, dt);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            DrawFPS(10,10);
            DrawText("Player Color", 10, 30, 14, mainPlayer->color);
            Player_draw(mainPlayer);
            
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

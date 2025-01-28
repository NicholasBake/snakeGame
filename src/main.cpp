#include <iostream>
//#include <chrono>
//#include <thread>
#include <raylib.h>
#include <array>
#include <vector>
#include "Tile.h"
#include "Snake.hpp"

Camera2D mainCamera = { 0 };

const std::size_t rows = 9;
const std::size_t collumns = 9;
std::array<std::array<Tile, collumns>, rows> Map;

std::vector<Snake> snakeBody;

constexpr int screenWidth = 1000;
constexpr int screenHeight = 800;

// elapsedTime is increased by the time inbetween frames (deltaTime). This is used as the time step mechanic of the main game loop, as it allows me to always render to the screen but only update game logic every time stepw
float elapsedTime = 0;
    
// interval in which the Running method should be called. 
float timeStepTime = 0.25;

enum GameState{
    PLAYING,
    PAUSED,
    GAMEOVER
};

GameState gameState = PLAYING;


void GameLogic(int lastKeyPressed){
        // First scan for input and then change direction of the snake head (snakeBody[0]) accordingly
        if(lastKeyPressed == KEY_W){
            if(snakeBody[0].DIRECTION != 3){
                snakeBody[0].DIRECTION = 1;
            }
        }
        if(lastKeyPressed == KEY_D){
            if(snakeBody[0].DIRECTION != 4){
                snakeBody[0].DIRECTION = 2;
            }    
        }
        if(lastKeyPressed == KEY_S){
            if(snakeBody[0].DIRECTION != 1){
                snakeBody[0].DIRECTION = 3;
            }
        }
        if(lastKeyPressed == KEY_A){
            if(snakeBody[0].DIRECTION != 2){
                 snakeBody[0].DIRECTION = 4;
            }
                    
        }
            
        // TODO : The map only updates the isSnake tiles in the loop where the X and Y of the current snake objects in the snakebody vector is updated. Change it so that at the end of all updates to the snake, actually update tiles on the map's isSnake state. 
        // Then change the X or Y of each snake node according to their direction
        for (int i = 0; i < snakeBody.size(); i++)
        {
            switch (snakeBody.at(i).DIRECTION)
            {
            case 1:
                Map.at(snakeBody.at(i).Y).at(snakeBody.at(i).X).isSnake = false;

                Map.at(snakeBody.at(i).Y - 1).at(snakeBody.at(i).X).isSnake = true;

                snakeBody.at(i).Y--;

                break;
            case 2:
                Map.at(snakeBody.at(i).Y).at(snakeBody.at(i).X).isSnake = false;

                Map.at(snakeBody.at(i).Y).at(snakeBody.at(i).X + 1).isSnake = true;

                snakeBody.at(i).X++;

                break;
            case 3:
                Map.at(snakeBody.at(i).Y).at(snakeBody.at(i).X).isSnake = false;

                 Map.at(snakeBody.at(i).Y + 1).at(snakeBody.at(i).X).isSnake = true;

                snakeBody.at(i).Y++;

                break;
            case 4:
                Map.at(snakeBody.at(i).Y).at(snakeBody.at(i).X).isSnake = false;

                Map.at(snakeBody.at(i).Y).at(snakeBody.at(i).X - 1).isSnake = true;

                snakeBody.at(i).X--;

                break;
            }
        }
            
        // Now that the snake has moved lets check if the snake head is on a food tile or is dead
        // Checking first if the head tile's x and y equal any other snake node's x and y
        for (int i = 1; i < snakeBody.size(); i++)
        {       
            if(snakeBody.at(i).X == snakeBody.at(0).X && snakeBody.at(i).Y == snakeBody.at(0).Y){
                gameState = GAMEOVER;
                return;
            }
        }
        
        // If the head's X and Y are on a food tile add to the end of the snake and then choose where the next food tile will be
        if(Map.at(snakeBody.at(0).Y).at(snakeBody.at(0).X).isFood){

            //std::cout << "ran" << std::endl;

            Snake snakeToAdd = Snake(snakeBody.at(snakeBody.size() - 1).X, snakeBody.at(snakeBody.size() - 1).Y);
            snakeToAdd.DIRECTION = snakeBody.at(snakeBody.size()-1).DIRECTION;

            if(snakeToAdd.DIRECTION == 1){
                snakeToAdd.Y++;
            }
            if(snakeToAdd.DIRECTION == 2){
                snakeToAdd.X--;
            }
            if(snakeToAdd.DIRECTION == 3){
                snakeToAdd.Y--;
            }
            if(snakeToAdd.DIRECTION == 4){
                snakeToAdd.X++;
            }

            snakeBody.push_back(snakeToAdd);

            Map.at(snakeBody.at(0).Y).at(snakeBody.at(0).X).isFood = false;
            // have to do - 1 at the end because when initializing map array the size includes index 0 (so size 9 is 0,1,2,3,4,5,6,7,8 which is nine elementsw)
            Map.at(GetRandomValue(0, collumns - 1)).at(GetRandomValue(0, rows - 1)).isFood = true;
        }
        
        /*if(Map.at(snakeBody.at(0).Y).at(snakeBody.at(0).X).isSnake ){
            gameState = GAMEOVER;
        }*/
        // Change snake nodes directions according to new positions

        // First - Copy old directions into vector
        std::vector<int> old;
        for (int i = 0; i < snakeBody.size(); i++)
         {
            old.push_back(snakeBody[i].DIRECTION);
        }
        // Then update snakebody using the old directions
        for (int i = 1; i < snakeBody.size(); i++)
        {
            snakeBody.at(i).DIRECTION = old.at(i - 1);
        }
}
void Paused(){
    DrawText(TextFormat("PAUSED, PRESS F1 TO UNPAUSE"), screenWidth/2 - 200, screenHeight/2, 30, RED);
    if(IsKeyDown(KEY_F1)){
        ///std::cout << "UNPAUSED" << std::endl;
        gameState = PLAYING;
        return;
    }
    
}
void GameOver(){
    DrawText(TextFormat("GAME OVER"), 0, 0, 300, RED);
    if(IsKeyDown(KEY_F1)){
        ///std::cout << "UNPAUSED" << std::endl;
        gameState = PLAYING;
        return;
    }
}
// Method where we, well render. Using game logic updated every timestep, it renders each tile deciding its' color based on if the tile is a snake, food, or normal tile.
void Render(){
        BeginDrawing();
            mainCamera.zoom = 0.10;
            BeginMode2D(mainCamera);
            int startX = mainCamera.offset.x;
            int startY = mainCamera.offset.y; 
            // Draw all tiles inside of Map, using startX and startY as an offset moving where the rows should start
            if(gameState == GAMEOVER){
                GameOver();
            }
            if(gameState == PAUSED){
                Paused();
            }
            for (int i = 0; i < Map.size(); i++){

                for (int j = 0; j < Map.at(i).size(); j++){

                    Tile &tile = Map.at(i).at(j);
                    if(tile.isFood){
                        DrawRectangle(startX, startY, tile.XY, tile.XY, RED);    
                    }
                    if(tile.isSnake){
                        if(i == snakeBody.at(0).Y && j == snakeBody.at(0).X){
                            DrawRectangle(startX, startY, tile.XY, tile.XY, DARKGREEN);    
                        }
                        else{
                            DrawRectangle(startX, startY, tile.XY, tile.XY, GREEN);
                        }    
                    }
                    if(tile.isFood == false && tile.isSnake == false){
                        DrawRectangle(startX , startY, tile.XY, tile.XY, tile.tileColor);
                    }
                    startX += tile.XY;

                    if(j >= Map.at(i).size() - 1){
                        startY += tile.XY;
                    }

                }
                startX = mainCamera.offset.x;
            }
            ClearBackground(DARKPURPLE);
            EndMode2D();
        EndDrawing();
}

int main() 
{   
    InitWindow(screenWidth, screenHeight, "Snake!");
    SetTargetFPS(60);

    
    
    // Initializing the map
    int checkerPatternOffset = 0;
    for (int i = 0; i < Map.size(); i++)
    {
        for (int j = 0; j < Map.at(i).size(); j++)
        {
            //int startX = 50;
            //int startY = 50;

            if(checkerPatternOffset % 2 == 0){
                Tile tile = Tile(WHITE, 300, false, false);
                Map[i][j] = tile;
            }
            else{
                Tile tile = Tile(BLACK, 300, false, false);
                Map[i][j] = tile;
            }
            checkerPatternOffset++;
        }
    }
    
    // where the snake will start
    Map[3][3].isSnake = true;
    Map.at(6).at(6).isFood = true;
    //Map[2][3].isSnake = true;
    
    // snakeBody[0] is the head of the snake
    
    snakeBody.push_back(Snake(3, 3));
    snakeBody.push_back(Snake(2, 3));
    snakeBody.push_back(Snake(1, 3));
    snakeBody.push_back(Snake(0, 3));
    snakeBody[0].DIRECTION = 2;
    snakeBody[1].DIRECTION = 2;
    snakeBody[2].DIRECTION = 2;
    snakeBody[3].DIRECTION = 2;

    mainCamera.offset = (Vector2){ screenWidth/2,  screenHeight/2 };
    mainCamera.target = (Vector2){ 1000, 800 };
    //mainCamera.zoom = 1;

    /* GAME LOOP */
    int lastKeyPressed = 0;
    while (!WindowShouldClose())
    {
        // This is here so we can pass our input into the GameLogic function outside of the actual gamelogic function (as that function only runs every time step)
        int keyPressed = GetKeyPressed();
        if(keyPressed != 0){
            lastKeyPressed = keyPressed;
        }
        
        if(lastKeyPressed == KEY_Q && gameState != PAUSED){
            gameState = PAUSED;
        }
        
        if(gameState == PLAYING && elapsedTime >= timeStepTime){
            GameLogic(lastKeyPressed);
            elapsedTime = 0;
        }
        Render();
        //sstd::this_thread::sleep_for(std::chrono::milliseconds(200));
        elapsedTime += GetFrameTime();

        std::cout << "GAME STATE " << gameState << std::endl;
    }
    
    CloseWindow();
    return 0;
}

#include <iostream>
#include "raylib.h"
#include <string>
using namespace std;

bool gameOver = false;
string winner = "";
string board[3][3];
string currentPlayer = "x";


void initGame() {
    currentPlayer = "x";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            board[i][j] = "";
            
        }
    }
}

void nextTurn() {
    if (currentPlayer == "x") {
        currentPlayer = "o";
    }
    else {
        currentPlayer = "x";
    }
}

void drawBoard() {
    //Draws vertical lines
    DrawLine(200, 600, 200, 0, BLACK);
    DrawLine(400, 600, 400, 0, BLACK);
    //Draws horizontal lines
    DrawLine(0, 400, 600, 400, BLACK);
    DrawLine(0, 200, 600, 200, BLACK);
}

bool inRange(float low, float high, float x) {
    if (x > low && x < high) {
        return true;
    }
    else {
        return false;
    }
}


void checkForWin() {
    //kinda got lazy here 
    for (int i = 0; i < 3; i++) {
        
        //horizontal
        if ( ((board[i][0] == "x") && (board[i][1] == "x") && (board[i][2] == "x")) || ((board[i][0] == "o") && (board[i][1] == "o") && (board[i][2] == "o")) ) {
            gameOver = true;
        }
        //vertical
        else if( ((board[0][i] == "x") && (board[1][i] == "x") && (board[2][i] == "x")) || ((board[0][i] == "o") && (board[1][i] == "o") && (board[2][i] == "o")) ) {
            gameOver = true;
        }
        //diagonal
        else if ( ((board[0][0] == "x") && (board[1][1] == "x") && (board[2][2] == "x")) || ((board[0][0] == "o") && (board[1][1] == "o") && (board[2][2] == "o")) ) {
            gameOver = true;
        }
        else if (((board[0][2] == "x") && (board[1][1] == "x") && (board[2][0] == "x")) || ((board[0][2] == "o") && (board[1][1] == "o") && (board[2][0] == "o"))) {
            gameOver = true;
        }
        
    }
}


int main(void)
{
    //initialize
    InitWindow(600, 600, "Tic Tac Toe");
    SetTargetFPS(60);

    //initialize game
    initGame();

    while (!WindowShouldClose())
    {

        //Begine drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        if (!gameOver) {
            drawBoard();

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                float mouseX = GetMouseX();
                float mouseY = GetMouseY();

                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {

                        if ((inRange((i * 200), ((i + 1) * 200), mouseX)) && (inRange((j * 200), ((j + 1) * 200), mouseY))) {
                            if (board[j][i] == "") {
                                winner = "currentPlayer";

                                board[j][i] = currentPlayer;
                                nextTurn();
                            }
                        }
                    }
                }
            }



            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {

                    if (board[i][j] == "x") {

                        DrawText("x", (200 * j) + 5, (200 * i) - 109, 380, BLACK);
                        checkForWin();
                    }
                    else if (board[i][j] == "o") {
                        DrawText("o", (200 * j) + 5, (200 * i) - 109, 380, BLACK);
                        checkForWin();

                    }
                }
            }

        }
        else {
            DrawText("Click ENTER to play again", GetScreenWidth() / 2 - MeasureText("Click ENTER to play again", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);
            if (IsKeyPressed(KEY_ENTER)) {
                initGame();
                gameOver = false;
            }
        }
        


        DrawFPS(0,0);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
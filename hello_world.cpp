#include "raylib.h"

struct Ball {
    float Xpos, Ypos;
    int Radius;
    float Xmovespeed, Ymovespeed;

    void Draw() {
        DrawCircle(Xpos, Ypos, Radius, WHITE);
    }
};

struct Paddle {
    float x, y;
    int width, height;
    float speed, Yspeed;

    void Draw() {
        DrawRectangle(x, y, width, height, WHITE);
    }
};

int main(void)
{

    const int screenWidth = 1280;
    const int screenHeight = 720;

    Ball ball;
    
    ball.Xpos = screenWidth / 2.0f;
    ball.Ypos = screenHeight / 2.0f;
    ball.Radius = 15;
    ball.Xmovespeed = 300;
    ball.Ymovespeed = 300;

    Paddle leftPaddle;

    leftPaddle.x = 75;
    leftPaddle.y = screenHeight / 2.0f;
    leftPaddle.width = 10;
    leftPaddle.height = 150;
    leftPaddle.Yspeed = 400;

    Paddle rightPaddle;

    rightPaddle.x = screenWidth - 75 - 10;
    rightPaddle.y = screenHeight / 2.0f;
    rightPaddle.width = 10;
    rightPaddle.height = 150;
    rightPaddle.Yspeed = 400;
    
    InitWindow(screenWidth, screenHeight, "first basic window");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        ball.Xpos += ball.Xmovespeed * GetFrameTime();
        ball.Ypos += ball.Ymovespeed * GetFrameTime();

        rightPaddle.speed = rightPaddle.Yspeed * GetFrameTime();
        leftPaddle.speed = leftPaddle.Yspeed * GetFrameTime();
        
        if (IsKeyDown(KEY_W)) {
            if(leftPaddle.y > 0) {
                leftPaddle.y -= leftPaddle.speed;
            }
        }

        if (IsKeyDown(KEY_S)) {
            if(leftPaddle.y + leftPaddle.height < screenHeight) {
                leftPaddle.y += leftPaddle.speed;
            }
        }

        if (IsKeyDown(KEY_I)) {
            if(rightPaddle.y > 0) {
                rightPaddle.y -= rightPaddle.speed;
            }
        }

        if (IsKeyDown(KEY_K)) {
            if(rightPaddle.y + rightPaddle.height < screenHeight) {
                rightPaddle.y += rightPaddle.speed;
            }
        }
        
        if (ball.Ypos > screenHeight - ball.Radius || ball.Ypos - ball.Radius < 0) {
            ball.Ymovespeed *= -1;
        }

        if (ball.Xpos < 0 - ball.Radius * 4 || ball.Xpos > screenWidth + ball.Radius * 4) {
            ball.Xpos = screenWidth / 2.0f;
            ball.Ypos = screenHeight / 2.0f;
            ball.Xmovespeed = 300;
            ball.Ymovespeed = 300;
        }

        if ((ball.Xpos + ball.Radius > rightPaddle.x + rightPaddle.width / 2) && (ball.Xpos < rightPaddle.x + rightPaddle.width) && (ball.Ypos + 10 > rightPaddle.y) && (ball.Ypos - 10 < rightPaddle.y + rightPaddle.height)) {
            if (ball.Xmovespeed > 0) {
                if(ball.Ymovespeed * ball.Xmovespeed > 0) {
                    if(IsKeyDown(KEY_K)) {
                        ball.Ymovespeed += rightPaddle.Yspeed;
                    }
                    if(IsKeyDown(KEY_I)) {
                        ball.Ymovespeed -= rightPaddle.Yspeed;
                    }
                }
                if(ball.Ymovespeed * ball.Xmovespeed < 0) {
                    if(IsKeyDown(KEY_I)) {
                        ball.Ymovespeed += rightPaddle.Yspeed;
                    }
                    if(IsKeyDown(KEY_K)) {
                        ball.Ymovespeed -= rightPaddle.Yspeed;
                    }
                }

                ball.Xmovespeed *= -1; //Player 2 collision
            }
        }

        if ((ball.Xpos - ball.Radius < leftPaddle.x + leftPaddle.width / 2) && (ball.Xpos > leftPaddle.x + leftPaddle.width) && (ball.Ypos + 10 > leftPaddle.y) && (ball.Ypos - 10 < leftPaddle.y + leftPaddle.height)) {
            if (ball.Xmovespeed < 0) {            
                if(ball.Ymovespeed * ball.Xmovespeed > 0) {
                    if(IsKeyDown(KEY_S)) {
                        ball.Ymovespeed += leftPaddle.Yspeed;
                    }
                    if(IsKeyDown(KEY_W)) {
                        ball.Ymovespeed -= leftPaddle.Yspeed;
                    }
                }
                if(ball.Ymovespeed * ball.Xmovespeed < 0) {
                    if(IsKeyDown(KEY_W)) {
                        ball.Ymovespeed += leftPaddle.Yspeed;
                    }
                    if(IsKeyDown(KEY_S)) {
                        ball.Ymovespeed -= leftPaddle.Yspeed;
                    }
                }

                ball.Xmovespeed *= -1; //Player 1 collision
            }
        }
        
        BeginDrawing();
            ClearBackground(BLACK);
            //DrawText("without the raylib folder", 640, 360, 20, LIGHTGRAY);
            DrawFPS(20, 20);

            ball.Draw();
            leftPaddle.Draw();
            rightPaddle.Draw();
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
};

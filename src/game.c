#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>
#include <raymath.h>

#include "player.h"
#include "ball.h"
#include "camera.h"
#include "item.h"

#define TITLE "Around and Around"
#define ICON "resources/icon.png"
#define WIDTH 800
#define HEIGHT 450
#define FPS 60

#define PLAYER_BALL_IMAGE "resources/img/ball1.png"
#define ITEM_BALL_IMAGE "resources/img/ball2.png"

Ball b1, b2;
Player player;
Camera2D camera;
Item *items;

static void Initialize(void);
static void MainLoop(void);

int main()
{
    // ~ Initialization
    Initialize();

    SetTargetFPS(FPS);
    // ~ Main loop
    while (!WindowShouldClose())
    {
        MainLoop();
    }

    // ~ De-Initialization
    FreeItems(items);
    CloseWindow();

    return 0;
}

static void Initialize()
{
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetWindowIcon(LoadImage(ICON));

    CreateBallImage(&b1, (Vector2){WIDTH / 2, HEIGHT / 2}, PLAYER_BALL_RADIUS, LoadTexture(PLAYER_BALL_IMAGE));
    CreateBallImage(&b2, (Vector2){WIDTH / 2, HEIGHT / 2}, PLAYER_BALL_RADIUS, LoadTexture(PLAYER_BALL_IMAGE));

    CreatePlayer(&player, &b1, &b2);
    CreateCamera(&camera, WIDTH, HEIGHT);
    CreateItems(&items, MAX_ITEMS, ITEM_BALL_RADIUS);
    ScatterItems(items, camera, PLAYER_RADIUS);
}

static void MainLoop()
{
    // ~ Input
    if (IsKeyPressed(KEY_SPACE))
        SwapBalls(&player);

    // ~ Update
    UpdatePlayer(&player);
    UpdateCameraTarget(&camera, player.pivotBall->position, CAMERA_FOLLOW_SPEED);
    CheckItemCollisions(items, &player, camera, PLAYER_RADIUS);

    // ~ Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(camera);
    DrawItems(items);
    DrawPlayer(&player);
    EndMode2D();

    // ~ Draw UI
    DrawUI(&player);
    EndDrawing();
}

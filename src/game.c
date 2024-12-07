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

#define CAMERA_FOLLOW_SPEED 0.1f
#define BALL_RADIUS 10
#define PLAYER_RADIUS 150
#define PLAYER_SPEED 5.0f
#define MAX_ITEMS 10
#define ITEM_RADIUS 10

Ball b1, b2;
Player player;
Camera2D camera;
Item items[MAX_ITEMS];

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
    CloseWindow();

    return 0;
}

static void Initialize()
{
    InitWindow(WIDTH, HEIGHT, TITLE);
    SetWindowIcon(LoadImage(ICON));

    CreateBall(&b1, (Vector2){WIDTH / 2, HEIGHT / 2}, BLUE, BALL_RADIUS);
    CreateBall(&b2, (Vector2){WIDTH / 2, HEIGHT / 2}, RED, BALL_RADIUS);
    CreatePlayer(&player, &b1, &b2, PLAYER_RADIUS, PLAYER_SPEED);
    CreateCamera(&camera, WIDTH, HEIGHT);
    CreateItems(items, MAX_ITEMS, GREEN, ITEM_RADIUS, 1);
    ScatterItems(items, MAX_ITEMS, camera, PLAYER_RADIUS);
}

static void MainLoop()
{
    // ~ Input
    if (IsKeyPressed(KEY_SPACE))
        SwapBalls(&player);

    // ~ Update
    UpdatePlayer(&player);
    UpdateCameraTarget(&camera, player.pivotBall->position, CAMERA_FOLLOW_SPEED);
    CheckItemCollisions(items, MAX_ITEMS, &player, camera, PLAYER_RADIUS);

    // ~ Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(camera);
    DrawItems(items, MAX_ITEMS);
    DrawPlayer(&player);
    EndMode2D();

    // ~ Draw UI
    DrawUI(&player);
    EndDrawing();
}

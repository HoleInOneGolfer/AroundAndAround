#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <raymath.h>

#include "ball.h"

#define PLAYER_LINE_THICKNESS 5.0f
#define PLAYER_BALL_RADIUS 10.0f

#define PLAYER_MAX_SPEED 10.0f
#define PLAYER_MIN_SPEED 1.0f
#define PLAYER_SPEED 5.0f

#define PLAYER_RADIUS 150.0f

typedef struct Player
{
    Ball *pivotBall;
    Ball *activeBall;

    float theta;
    float speed;
    float radius;

    int direction;
    int score;
} Player;

void CreatePlayer(Player *player, Ball *pivotBall, Ball *activeBall);
void SwapBalls(Player *player);
void DrawPlayer(Player *player);
void UpdatePlayer(Player *player);

float DistanceToLine(Vector2 point, Vector2 line_start, Vector2 line_end);

void DrawUI(Player *player);

#endif // PLAYER_H

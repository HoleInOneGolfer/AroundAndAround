#ifndef BALL_H
#define BALL_H

#include <raylib.h>
#include <raymath.h>

typedef enum BallDrawMode
{
    BALL_DRAW_IMAGE,
    BALL_DRAW_COLOR,
} BallDrawMode;

typedef union BallDrawData
{
    Texture2D texture;
    Color color;
} BallDrawData;

typedef struct Ball
{
    Vector2 position;
    float radius;
    BallDrawMode drawMode;
    BallDrawData drawData;
} Ball;

void CreateBall(Ball *ball, Vector2 position, float radius, BallDrawData drawData, BallDrawMode drawMode);
void CreateBallImage(Ball *ball, Vector2 position, float radius, Texture2D texture);
void CreateBallColor(Ball *ball, Vector2 position, float radius, Color color);

void DrawBall(Ball *ball);

#endif // BALL_H

#ifndef BALL_H
#define BALL_H

#include <raylib.h>
#include <raymath.h>

typedef struct Ball
{
    Vector2 position;
    Color color;
    float radius;
} Ball;

void CreateBall(Ball *ball, Vector2 position, Color color, float radius);
void DrawBall(Ball *ball);

#endif // BALL_H

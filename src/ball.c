#include "ball.h"

void CreateBall(Ball *ball, Vector2 position, Color color, float radius)
{
    ball->position = position;
    ball->color = color;
    ball->radius = radius;
}

void DrawBall(Ball *ball)
{
    DrawCircleV(ball->position, ball->radius, ball->color);
}

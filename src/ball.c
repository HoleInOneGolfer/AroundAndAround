#include "ball.h"

void CreateBall(Ball *ball, Vector2 position, float radius, BallDrawData drawData, BallDrawMode drawMode)
{
    *ball = (Ball){
        .position = position,
        .radius = radius,
        .drawMode = drawMode,
        .drawData = drawData,
    };
}

void CreateBallImage(Ball *ball, Vector2 position, float radius, Texture2D texture)
{
    *ball = (Ball){
        .position = position,
        .radius = radius,
        .drawMode = BALL_DRAW_IMAGE,
        .drawData = (BallDrawData){.texture = texture},
    };

    SetTextureFilter(texture, TEXTURE_FILTER_POINT);
}

void CreateBallColor(Ball *ball, Vector2 position, float radius, Color color)
{
    *ball = (Ball){
        .position = position,
        .radius = radius,
        .drawMode = BALL_DRAW_COLOR,
        .drawData = (BallDrawData){.color = color},
    };
}

void DrawBall(Ball *ball)
{
    switch (ball->drawMode)
    {
    case BALL_DRAW_IMAGE:
        float scale = ball->radius * 2 / ball->drawData.texture.width;

        DrawTextureEx(ball->drawData.texture, (Vector2){ball->position.x - ball->radius, ball->position.y - ball->radius}, 0, scale, WHITE);

        break;
    case BALL_DRAW_COLOR:
        DrawCircleV(ball->position, ball->radius, ball->drawData.color);
        break;
    default:
        break;
    }
}

#include "player.h"

void CreatePlayer(Player *player, Ball *pivotBall, Ball *activeBall, float radius, float speed)
{
    player->pivotBall = pivotBall;
    player->activeBall = activeBall;
    player->theta = 0;
    player->speed = speed;
    player->radius = radius;
    player->direction = 1;
    player->score = 0;
}

void DrawPlayer(Player *player)
{
    DrawLineEx(player->pivotBall->position, player->activeBall->position, PLAYER_LINE_THICKNESS, BLACK);
    DrawBall(player->pivotBall);
    DrawBall(player->activeBall);
}

void SwapBalls(Player *player)
{
    Ball *temp = player->pivotBall;
    player->pivotBall = player->activeBall;
    player->activeBall = temp;

    player->direction *= -1;

    player->theta = fmodf(player->theta + PI, 2 * PI);
}

void UpdatePlayer(Player *player)
{
    player->theta = fmodf(player->theta + player->speed * player->direction * GetFrameTime(), 2 * PI);

    player->activeBall->position = (Vector2){
        player->pivotBall->position.x + player->radius * cosf(player->theta),
        player->pivotBall->position.y + player->radius * sinf(player->theta),
    };
}

float DistanceToLine(Vector2 point, Vector2 line_start, Vector2 line_end)
{
    float x1 = line_start.x, y1 = line_start.y;
    float x2 = line_end.x, y2 = line_end.y;
    float px = point.x, py = point.y;

    float dx = x2 - x1;
    float dy = y2 - y1;

    float t = ((px - x1) * dx + (py - y1) * dy) / (dx * dx + dy * dy);
    t = fmaxf(0, fminf(1, t));

    float x = x1 + t * dx;
    float y = y1 + t * dy;

    x = px - x;
    y = py - y;

    return sqrtf(x * x + y * y);
}

void DrawUI(Player *player)
{
    DrawText(TextFormat("Score: %i", player->score), 10, 10, 20, BLACK);
    DrawText(TextFormat("Speed: %.2f", player->speed), 10, 40, 20, BLACK);
    DrawText(TextFormat("Direction: %s", player->direction == 1 ? "Clockwise" : "Counter-Clockwise"), 10, 70, 20, BLACK);
}

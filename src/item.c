#include "item.h"

void CreateItem(Item *item, ItemType type, Color color, float radius, int value)
{
    item->ball = (Ball){
        .position = Vector2Zero(),
        .color = color,
        .radius = radius,
    };
    item->value = value;
    item->type = type;
}

void CreateItems(Item items[], int count, Color color, float radius, int value)
{
    for (int i = 0; i < count; i++)
    {
        ItemType type = (ItemType)GetRandomValue(0, ITEM_FAST);
        CreateItem(&items[i], type, GetItemColor(type), radius, value);
    }
}

void DrawItem(Item *item)
{
    DrawBall(&item->ball);
}

void DrawItems(Item items[], int count)
{
    for (int i = 0; i < count; i++)
    {
        DrawItem(&items[i]);
    }
}

void ScatterItem(Item *item, Camera2D camera, float exclusion_radius)
{
    // Get camera bounds in world space
    Vector2 min = GetScreenToWorld2D((Vector2){0, 0}, camera);
    Vector2 max = GetScreenToWorld2D((Vector2){GetScreenWidth(), GetScreenHeight()}, camera);

    do
    {
        item->ball.position = (Vector2){
            GetRandomValue(min.x, max.x),
            GetRandomValue(min.y, max.y),
        };
    } while (Vector2Distance(item->ball.position, camera.target) < exclusion_radius);
}

void ScatterItems(Item items[], int count, Camera2D camera, float exclusion_radius)
{
    for (int i = 0; i < count; i++)
    {
        ScatterItem(&items[i], camera, exclusion_radius);
    }
}

void CheckItemCollision(Item *item, Player *player, Camera2D camera, float exclusion_radius)
{
    float dist = DistanceToLine(item->ball.position, player->pivotBall->position, player->activeBall->position);
    if (dist < item->ball.radius)
    {
        ItemCollide(item, player);
        ScatterItem(item, camera, exclusion_radius);
    }

    float dist2 = Vector2Distance(item->ball.position, player->pivotBall->position);
    if (dist2 > GetScreenWidth() + player->radius)
        ScatterItem(item, camera, exclusion_radius);
}

void CheckItemCollisions(Item items[], int count, Player *player, Camera2D camera, float exclusion_radius)
{
    for (int i = 0; i < count; i++)
    {
        CheckItemCollision(&items[i], player, camera, exclusion_radius);
    }
}

void ItemCollide(Item *item, Player *player)
{
    switch (item->type)
    {
    case ITEM_POINT:
        player->score += item->value;
        break;

    case ITEM_REVERSE:
        player->direction *= -1;
        break;

    case ITEM_SLOW:
        player->speed = Clamp(player->speed - item->value, PLAYER_MIN_SPEED, PLAYER_MAX_SPEED);
        break;

    case ITEM_FAST:
        player->speed = Clamp(player->speed + item->value, PLAYER_MIN_SPEED, PLAYER_MAX_SPEED);
        break;

    default:
        break;
    }
}

Color GetItemColor(ItemType type)
{
    switch (type)
    {
    case ITEM_POINT:
        return YELLOW;

    case ITEM_REVERSE:
        return ORANGE;

    case ITEM_SLOW:
        return MAROON;

    case ITEM_FAST:
        return GREEN;

    default:
        return GRAY;
    }
}

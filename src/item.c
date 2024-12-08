#include "item.h"

void CreateItem(Item *item, ItemType type, float radius)
{
    item->type = type;
    item->ball.position = Vector2Zero();
    item->ball.radius = radius;
    item->value = 0;

    switch (type)
    {
    case ITEM_POINT:
        item->value = 1;
        CreateBallImage(&item->ball, item->ball.position, item->ball.radius, LoadTexture("resources/img/ball2.png"));
        break;

    case ITEM_REVERSE:
        CreateBallColor(&item->ball, item->ball.position, item->ball.radius, RED);
        break;

    case ITEM_SLOW:
        CreateBallColor(&item->ball, item->ball.position, item->ball.radius, BLUE);
        break;

    case ITEM_FAST:
        CreateBallColor(&item->ball, item->ball.position, item->ball.radius, ORANGE);
        break;

    default:
    }
}

void CreateItems(Item **head, int count, float radius)
{
    for (int i = 0; i < count; i++)
    {
        Item *new_item = (Item *)malloc(sizeof(Item));
        ItemType type = (ItemType)GetRandomValue(0, ITEM_FAST);
        CreateItem(new_item, type, radius);
        new_item->next = *head; // Insert at the head
        *head = new_item;
    }
}

void DrawItem(Item *item)
{
    DrawBall(&item->ball);
}

void DrawItems(Item *head)
{
    Item *current = head;
    while (current != NULL)
    {
        DrawItem(current);
        current = current->next;
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

void ScatterItems(Item *head, Camera2D camera, float exclusion_radius)
{
    Item *current = head;
    while (current != NULL)
    {
        ScatterItem(current, camera, exclusion_radius);
        current = current->next;
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

void CheckItemCollisions(Item *head, Player *player, Camera2D camera, float exclusion_radius)
{
    Item *current = head;
    while (current != NULL)
    {
        CheckItemCollision(current, player, camera, exclusion_radius);
        current = current->next;
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

void FreeItems(Item *head)
{
    Item *current = head;
    while (current != NULL)
    {
        Item *next = current->next;
        free(current);
        current = next;
    }
}

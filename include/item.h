#ifndef ITEM_H
#define ITEM_H

#include <stdlib.h>

#include <raylib.h>
#include <raymath.h>

#include "player.h"
#include "ball.h"

#define ITEM_BALL_RADIUS 10.0f
#define MAX_ITEMS 10

typedef enum ItemType
{
    ITEM_POINT,
    ITEM_REVERSE,
    ITEM_SLOW,
    ITEM_FAST,
} ItemType;

typedef struct Item
{
    int value;
    ItemType type;
    Ball ball;

    struct Item *next;
} Item;

void CreateItem(Item *item, ItemType type, float radius);
void CreateItems(Item **head, int count, float radius);

void DrawItem(Item *item);
void DrawItems(Item *head);

void ScatterItem(Item *item, Camera2D camera, float exclusion_radius);
void ScatterItems(Item *head, Camera2D camera, float exclusion_radius);

void CheckItemCollision(Item *item, Player *player, Camera2D camera, float exclusion_radius);
void CheckItemCollisions(Item *head, Player *player, Camera2D camera, float exclusion_radius);

void ItemCollide(Item *item, Player *player);

void FreeItems(Item *head);

#endif // ITEM_H

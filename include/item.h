#ifndef ITEM_H
#define ITEM_H

#include <raylib.h>
#include <raymath.h>

#include "player.h"
#include "ball.h"

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
} Item;

void CreateItem(Item *item, ItemType type, float radius);
void CreateItems(Item item[], int count, float radius);

void DrawItem(Item *item);
void DrawItems(Item items[], int count);

void ScatterItem(Item *item, Camera2D camera, float exclusion_radius);
void ScatterItems(Item items[], int count, Camera2D camera, float exclusion_radius);

void CheckItemCollision(Item *item, Player *player, Camera2D camera, float exclusion_radius);
void CheckItemCollisions(Item items[], int count, Player *player, Camera2D camera, float exclusion_radius);

void ItemCollide(Item *item, Player *player);

#endif // ITEM_H

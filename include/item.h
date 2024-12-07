#ifndef ITEM_H
#define ITEM_H

#include <raylib.h>
#include <raymath.h>

#include "player.h"

typedef enum ItemType
{
    ITEM_POINT,
    ITEM_REVERSE,
    ITEM_SLOW,
    ITEM_FAST,
} ItemType;

typedef struct Item
{
    Vector2 position;
    Color color;
    float radius;
    int value;
    ItemType type;
} Item;

void CreateItem(Item *item, ItemType type, Color color, float radius, int value);
void CreateItems(Item item[], int count, Color color, float radius, int value);

void DrawItem(Item *item);
void DrawItems(Item items[], int count);

void ScatterItem(Item *item, Camera2D camera, float exclusion_radius);
void ScatterItems(Item items[], int count, Camera2D camera, float exclusion_radius);

void CheckItemCollision(Item *item, Player *player, Camera2D camera, float exclusion_radius);
void CheckItemCollisions(Item items[], int count, Player *player, Camera2D camera, float exclusion_radius);

void ItemCollide(Item *item, Player *player);

Color GetItemColor(ItemType type);

#endif // ITEM_H

#ifndef TILE_H
#define TILE_H
#include "raylib.h"
#include "figure.h"
#include <stdlib.h>

typedef struct Figure Figure;

typedef struct Tile
{
    Vector2 pos;
    Figure* figure;
    
    enum
    {
        WHITE_TILE,
        BLACK_TILE
    } color;

    int x;
    int y;

} Tile;

Tile* init_tile(int color, Vector2 pos);
void draw_tile(Texture2D tile_spritesheet, Tile* tile);
Rectangle get_tile_rec(Tile* tile);
void move_figure(int* player_turn, Tile** selected_tile, Tile** move_to_tile);

#endif
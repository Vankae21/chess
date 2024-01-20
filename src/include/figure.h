#ifndef FIGURE_H
#define FIGURE_H
#include "raylib.h"
#include "tile.h"
#include "game.h"
#include <stdlib.h>

typedef struct Tile Tile;

typedef struct Figure
{
    enum
    {
        PAWN,
        ROOK,
        KNIGHT,
        BISHOP,
        QUEEN,
        KING
    } type;

    enum
    {
        WHITE_F,
        BLACK_F
    } color;

    Tile* tile;

} Figure;

Figure* init_figure(int type, int color, Tile* tile);
void draw_figure(Texture2D figure_spritesheet, Figure* figure);
Rectangle get_figure_rec(Figure* figure);

#endif
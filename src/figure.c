#include "include/figure.h"
#include "include/tile.h"

Figure* init_figure(int type, int color, Tile* tile)
{
    Figure* figure = calloc(1, sizeof(Figure));

    figure->type = type;
    figure->color = color;
    tile->figure = figure;

    //for only pos purpose
    figure->tile = tile;


    return figure;
}
void draw_figure(Texture2D figure_spritesheet, Figure* figure)
{
    DrawTexturePro(figure_spritesheet, (Rectangle){ .x = figure->type * TILE_SIZE, .y = figure->color * TILE_SIZE, .width = TILE_SIZE, .height = TILE_SIZE },
    get_figure_rec(figure), (Vector2){ 0 }, 0, WHITE );
}
Rectangle get_figure_rec(Figure* figure)
{
    return (Rectangle){ .x = figure->tile->pos.x + TILE_SIZE / 2, .y = figure->tile->pos.y + TILE_SIZE / 2 , .width = TILE_SIZE * 4, .height = TILE_SIZE * 4 };
}
#include "include/tile.h"
#include "include/game.h"
#include "include/figure.h"

Tile* init_tile(int color, Vector2 pos)
{
    Tile* tile = calloc(1, sizeof(Tile));

    tile->pos = pos;
    tile->color = color;

    tile->figure = NULL;

    tile->x = 0;
    tile->y = 0;

    return tile;
}
void draw_tile(Texture2D tile_spritesheet, Tile* tile)
{
    DrawTexturePro(tile_spritesheet, (Rectangle){ .x = tile->color * TILE_SIZE, .y = 0, .width = TILE_SIZE, .height = TILE_SIZE },
    get_tile_rec(tile), (Vector2){ 0 }, 0, WHITE );
}
Rectangle get_tile_rec(Tile* tile)
{
    return (Rectangle){ .x = tile->pos.x, .y = tile->pos.y, .width = TILE_SIZE * SIZE_MULTIPLIER , .height = TILE_SIZE * SIZE_MULTIPLIER };
}
void move_figure(int* player_turn, Tile** selected_tile, Tile** move_to_tile)
{
    if (*selected_tile == NULL || *move_to_tile == NULL) return;

    switch (*player_turn)
    {
        case WHITE_F:
            switch ((*selected_tile)->figure->type)
            {
                case PAWN:
                    // a step
                    if ((*move_to_tile)->figure == NULL && ((*selected_tile)->y - 1 == (*move_to_tile)->y
                    // two steps if hasn't moved yet
                    || ((*selected_tile)->y == 6 && (*selected_tile)->y - 2 == (*move_to_tile)->y)) && (*selected_tile)->x == (*move_to_tile)->x)
                    {
                        (*selected_tile)->figure->tile = *move_to_tile;
                        (*move_to_tile)->figure = (*selected_tile)->figure;
                        (*selected_tile)->figure = NULL;
                        *selected_tile = NULL;
                        *move_to_tile = NULL;

                        // change turn
                        *player_turn = BLACK_F;
                    }

                    // hit figure
                    else if((*move_to_tile)->figure != NULL && (*move_to_tile)->figure->color == BLACK_F && (*selected_tile)->y - 1 == (*move_to_tile)->y && ((*selected_tile)->x - 1 == (*move_to_tile)->x || (*selected_tile)->x + 1 == (*move_to_tile)->x))
                    {
                        free((*move_to_tile)->figure);
                        (*selected_tile)->figure->tile = *move_to_tile;
                        (*move_to_tile)->figure = (*selected_tile)->figure;
                        (*selected_tile)->figure = NULL;
                        *selected_tile = NULL;
                        *move_to_tile = NULL;

                        // change turn
                        *player_turn = BLACK_F;
                    }
                    break;
                default:
                    printf("Not pawn\n");
                    break;
            }
            break;
        case BLACK_F:
            switch ((*selected_tile)->figure->type)
            {
                case PAWN:
                    // a step
                    if (((*move_to_tile)->figure == NULL && ((*selected_tile)->y + 1 == (*move_to_tile)->y 
                    // two steps if hasn't moved yet
                    || ((*selected_tile)->y == 1 && (*selected_tile)->y + 2 == (*move_to_tile)->y)) && (*selected_tile)->x == (*move_to_tile)->x))                 
                    {
                        (*selected_tile)->figure->tile = *move_to_tile;
                        (*move_to_tile)->figure = (*selected_tile)->figure;
                        (*selected_tile)->figure = NULL;
                        *selected_tile = NULL;
                        *move_to_tile = NULL;

                        // change turn
                        *player_turn = WHITE_F;
                    }

                    // hit figure
                    else if((*move_to_tile)->figure != NULL && (*move_to_tile)->figure->color == WHITE_F && (*selected_tile)->y + 1 == (*move_to_tile)->y && ((*selected_tile)->x - 1 == (*move_to_tile)->x || (*selected_tile)->x + 1 == (*move_to_tile)->x))
                    {
                        free((*move_to_tile)->figure);
                        (*selected_tile)->figure->tile = *move_to_tile;
                        (*move_to_tile)->figure = (*selected_tile)->figure;
                        (*selected_tile)->figure = NULL;
                        *selected_tile = NULL;
                        *move_to_tile = NULL;

                        // change turn
                        *player_turn = WHITE_F;
                    }
                    break;
                default:
                    printf("Not pawn\n");
                    break;
            }
            break;
        default:
            printf("Color error\n");
            break;
    }

    *move_to_tile = NULL;
    *selected_tile = NULL;
}

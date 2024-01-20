#include "include/game.h"
#include "include/tile.h"
#include "include/figure.h"
#include <time.h>

bool DEBUG = true;

const int WIDTH = 8 * TILE_SIZE * SIZE_MULTIPLIER;
const int HEIGHT = 8 * TILE_SIZE * SIZE_MULTIPLIER;

Tile* tiles[8][8];


Texture2D tile_spritesheet, figure_spritesheet;

int player_turn = 0;
Tile* selected_tile = NULL;
Tile* move_to_tile = NULL;


void init()
{
    srand(time(0));

    tile_spritesheet = LoadTexture("assets/tiles.png");
    figure_spritesheet = LoadTexture("assets/figures.png");

    Vector2 pos = { .x = 0, .y = 0 };
    int color = 0;


    //init tiles
    for(int i = 0; i < 8; i++)
    {
        pos.y = 0;
        for(int j = 0; j < 8; j++)
        {
            if(i % 2 == 0)
            {
                color = j % 2;
            }
            else
            {
                color = (j + 1) % 2;
            }

            tiles[i][j] = init_tile(color, pos);

            tiles[i][j]->x = i;
            tiles[i][j]->y = j;

            pos.y += TILE_SIZE * SIZE_MULTIPLIER;
        }
        pos.x += TILE_SIZE * SIZE_MULTIPLIER;
    }

    // init figures
    adjust();
}
void update()
{
    // if figure is NOT selected to move
    if(selected_tile == NULL)
    {
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(tiles[i][j]->figure == NULL) continue;
                if(tiles[i][j]->figure->color != player_turn) continue;

                if(CheckCollisionPointRec(GetMousePosition(), get_tile_rec(tiles[i][j])) && IsMouseButtonPressed(0))
                {
                    selected_tile = tiles[i][j];
                    printf("i: %d, j: %d, figure type: %d\n", i, j, tiles[i][j]->figure->type);
                    break;
                }
            }
        }
    }
    
    // if figure is selected to move
    else if(move_to_tile == NULL)
    {
        // deactivate selected tile
        if(CheckCollisionPointRec(GetMousePosition(), get_tile_rec(selected_tile)) && IsMouseButtonPressed(0))
        {
            selected_tile = NULL;
        }
        
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                if(CheckCollisionPointRec(GetMousePosition(), get_tile_rec(tiles[i][j])) && IsMouseButtonPressed(0))
                {
                    move_to_tile = tiles[i][j];
                    break;
                }
            }   
        }
    }

    move_figure(&player_turn, &selected_tile, &move_to_tile);
}
void late_update()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            draw_tile(tile_spritesheet, tiles[i][j]);
            if(tiles[i][j]->figure != NULL)
            {
                draw_figure(figure_spritesheet, tiles[i][j]->figure);
            }
        }
    }

    if(selected_tile != NULL)
    {
        DrawRectangleLinesEx(get_tile_rec(selected_tile), 3.4f, YELLOW);
    }

}
void end()
{

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            free(tiles[i][j]);
        }
    }
}

void adjust()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(tiles[i][j]->figure != NULL)
                free(tiles[i][j]->figure);
        }
    }

    // adjust
    for(int color = 0; color < 2; color++)
    {
        // pawn
        for(int i = 0; i < 8; i++)
        {
            switch(color)
            {
                case WHITE_F:
                    init_figure(PAWN, color, tiles[i][6]);
                    break;
                case BLACK_F:
                    init_figure(PAWN, color, tiles[i][1]);
                    break;
                default:
                    break;
            }
        }

        int y = color == WHITE_F ? 7 : 0;
        
        // rook
        for(int i = 0; i < 8; i += 7)
        {
            init_figure(ROOK, color, tiles[i][y]);
        }
        
        // knight
        for(int i = 1; i < 8; i += 5)
        {
            init_figure(KNIGHT, color, tiles[i][y]);
        }

        // bishop
        for(int i = 2; i < 8; i += 3)
        {
            init_figure(BISHOP, color, tiles[i][y]);
        }

        // queen 
        init_figure(QUEEN, color, tiles[3][y]);

        // king
        init_figure(KING, color, tiles[4][y]);
    }
}


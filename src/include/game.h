#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

extern const int WIDTH;
extern const int HEIGHT;

#define TITLE "Chess"
#define FPS 60
#define SIZE_MULTIPLIER 5
#define TILE_SIZE 16

extern bool DEBUG;

//main
void init();
void update();
void late_update();
void end();

//game
void adjust();


#endif
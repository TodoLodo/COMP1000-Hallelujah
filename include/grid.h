#ifndef _GRID_H
#define _GRID_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "random.h"

char **initGrid(unsigned short map_size[2], unsigned short player_pos[2], unsigned short goal_pos[2], unsigned short box_pos[2]);
void printGrid(char **grid, unsigned short map_size[2], unsigned short goal_pos[2], unsigned short box_pos[2]);
void move(char user_input, char **grid, unsigned short map_size[2], unsigned short player_pos[2], unsigned short goal_pos[2], unsigned short box_pos[2]);
void freeGrid(char **grid, unsigned short map_size[2]);
unsigned char winOrLose(char **grid, unsigned short map_size[2], unsigned short box_pos[2], unsigned short goal_pos[2]);

#endif
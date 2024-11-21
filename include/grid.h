#ifndef _GRID_H
#define _GRID_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "random.h"

char **initGrid(uint16_t map_size[2], uint16_t player_pos[2], uint16_t goal_pos[2]);
void printGrid(char **grid, uint16_t map_size[2]);
void movePlayer(char user_input, char **grid, uint16_t map_size[2], uint16_t player_pos[2]);
void freeGrid(char **grid, uint16_t map_size[2]);
uint8_t winOrLose(char **grid, uint16_t map_size[2], uint16_t player_pos[2], uint16_t goal_pos[2]);

#endif
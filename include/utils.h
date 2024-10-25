#ifndef _UTILS_H
#define _UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <terminal.h>

uint8_t argParser(int argc, char **argv, uint16_t map_size[2], uint16_t player_pos[2], uint16_t goal_pos[2]);
char getUserInput();

#endif
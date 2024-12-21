#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <terminal.h>

unsigned char argParser(int argc, char **argv, unsigned short map_size[2], unsigned short player_pos[2], unsigned short goal_pos[2]);
char getUserInput();

#endif
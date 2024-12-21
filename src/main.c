/*
	*******
	* P X *
	*   G *
	*******

	Filename: main.c
	Description: Main program to initialize, display, and control the gameplay grid
	Author: Todo Lodo
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "grid.h"
#include "random.h"

int main(int argc, char **argv)
{
	unsigned char running = 1, win_or_lose = 0;			  /* Control game loop and result */
	unsigned short map_size[2], player_pos[2], goal_pos[2]; /* Map dimensions and player/goal positions */
	char **grid = NULL;								  /* Grid representation */

	/* Parse and validate arguments, initialize map and player positions */
	if (argParser(argc, argv, map_size, player_pos, goal_pos))
	{
		/* Initialize grid and random number generator */
		grid = initGrid(map_size, player_pos, goal_pos);
		initRandom();

		if (grid != NULL)
		{
			/* Main gameplay loop */
			while (running)
			{
				/* Display the current grid */
				printGrid(grid, map_size);

				if (win_or_lose == 0) /* Game in progress */
				{
					/* Move player and check game status */
					movePlayer(getUserInput(), grid, map_size, player_pos);
					win_or_lose = winOrLose(grid, map_size, player_pos, goal_pos);
				}
				else if (win_or_lose) /* Game won or lost */
				{
					running = 0; /* Stop the game loop */

					/* Display win or lose message based on game outcome */
					switch (win_or_lose)
					{
					case 1:
						printf("You Win!\n");
						break;

					case 2:
						printf("You Lose!\n");
						break;

					default:
						break;
					}
				}
			}

			/* Free grid memory after gameplay */
			freeGrid(grid, map_size);
		}
	}

	return 0;
}

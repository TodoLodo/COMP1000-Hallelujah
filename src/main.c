/*
	*******
	* P X *
	*   G *
	*******

	Filename: main.c
	Description: Main program to initialize, display, and control the gameplay grid
	Author: Todo Lodo
*/

#include "utils.h"
#include "grid.h"
#include "random.h"

int main(int argc, char **argv)
{
	unsigned short map_size[2], player_pos[2], goal_pos[2]; /* Map dimensions and player/goal positions */
	char **grid = NULL;										/* Grid representation */

	/* Parse and validate arguments, initialize map and player positions */
	if (argParser(argc, argv, map_size, player_pos, goal_pos))
	{
		/* Initialize grid and random number generator */
		grid = initGrid(map_size, player_pos, goal_pos);
		initRandom();

		if (grid != NULL)
		{
			/* Display the current grid */
			printGrid(grid, map_size);
			
			/* Main gameplay loop */
			while (!winOrLose(grid, map_size, player_pos, goal_pos))
			{

				/* Move player and check game status */
				movePlayer(getUserInput(), grid, map_size, player_pos);

				/* Display the current grid */
				printGrid(grid, map_size);
			}

			/* Free grid memory after gameplay */
			freeGrid(grid, map_size);
		}
	}

	return 0;
}

/*
	*******
	* P X *
	*   G *
	*******

	Filename: grid.c
	Description: Defines the grid and player movement functionality, including initialization,
				 player movement, printing, and pathfinding using DFS.
	Author: Todo Lodo
*/

#include "grid.h"
#include "color.h"

void _initBox(unsigned short map_size[2], unsigned short player_pos[2], unsigned short goal_pos[2], unsigned short box_pos[2])
{
	memcpy(box_pos, player_pos, sizeof(short) * 2);

	/* Find a random empty spot and place an 'X' */
	while (memcmp(player_pos, box_pos, sizeof(short) * 2) == 0 || memcmp(goal_pos, box_pos, sizeof(short) * 2) == 0)
	{
		box_pos[0] = randomUCP(1, map_size[0] - 2);
		box_pos[1] = randomUCP(1, map_size[1] - 2);
	}
}

/* Initializes a 2D grid with specified dimensions and places player and goal at given positions */
char **initGrid(unsigned short map_size[2], unsigned short player_pos[2], unsigned short goal_pos[2], unsigned short box_pos[2])
{
	unsigned short row;
	char **grid = (char **)malloc(sizeof(char *) * map_size[0]); /* Allocate rows for grid */

	_initBox(map_size, player_pos, goal_pos, box_pos);

	if (grid != NULL)
	{
		/* Loop through rows, allocate columns, initialize empty spaces */
		for (row = 0; row < map_size[0]; row++)
		{
			grid[row] = (char *)malloc(sizeof(char) * (map_size[1] + 1)); /* Allocate memory for columns */

			if (grid[row] != NULL)
			{
				memset(grid[row], ' ', map_size[1]); /* Initialize row with empty spaces */

				/* Place player at specified position */
				if (row == player_pos[0])
				{
					grid[player_pos[0]][player_pos[1]] = 'P';
				}

				/* Place goal at specified position */
				if (row == goal_pos[0])
				{
					grid[goal_pos[0]][goal_pos[1]] = 'G';
				}

				/* Place box at specified position */
				if (row == box_pos[0])
				{
					grid[box_pos[0]][box_pos[1]] = 'B';
				}

				grid[row][map_size[1]] = '\0';
			}
			else
			{
				map_size[0] = row;
				freeGrid(grid, map_size); /* Free memory if allocation fails */
				grid = NULL;
				printf("Error: Failure in allocating memory for grid row! row=%u\n", row);
				row = map_size[0] - 1;
			}
		}
	}
	else
	{
		printf("Error: Failure in allocating memory for grid!\n");
	}

	return grid;
}

/* Prints the current grid state with borders */
void printGrid(char **grid, unsigned short map_size[2], unsigned short goal_pos[2], unsigned short box_pos[2])
{
	unsigned short i, j;
	char *h_border = malloc(sizeof(char) * (map_size[1] + 3));
	h_border[map_size[1] + 2] = '\0';
	memset(h_border, '*', map_size[1] + 2);

	system("clear");

	printf("%s\n", h_border);
	for (i = 0; i < map_size[0]; i++)
	{
		if (goal_pos[0] == i)
		{
			printf("*");
			for (j = 0; j < map_size[1]; j++)
			{
				if (goal_pos[1] == j)
				{
					if (memcmp(goal_pos, box_pos, sizeof(short) * 2) == 0)
					{
						setBackground("green");
					}
					else
					{
						setBackground("red");
					}
					printf("%c", grid[i][j]);
					setBackground("reset");
				}
				else
				{
					printf("%c", grid[i][j]);
				}
			}
			printf("*\n");
		}
		else
		{
			printf("*%s*\n", grid[i]);
		}
	}
	printf("%s\n", h_border);

	free(h_border);
}

/* Moves the player based on user input and checks border conditions */
void movePlayer(char user_input, char **grid, unsigned short map_size[2], unsigned short player_pos[2], unsigned short goal_pos[2], unsigned short box_pos[2])
{
	int future_player_pos[2], future_box_pos[2];

	future_player_pos[0] = (int)player_pos[0];
	future_player_pos[1] = (int)player_pos[1];

	/* Update future position based on input */
	switch (user_input)
	{
	case 'w':
		future_player_pos[0]--;
		break;

	case 's':
		future_player_pos[0]++;
		break;

	case 'a':
		future_player_pos[1]--;
		break;

	case 'd':
		future_player_pos[1]++;
		break;

	default:
		break;
	}

	/* Move player to future position if accessible */
	if (!(future_player_pos[0] == (int)player_pos[0] && future_player_pos[1] == (int)player_pos[1]) && future_player_pos[0] >= 0 && future_player_pos[0] < map_size[0] && future_player_pos[1] >= 0 && future_player_pos[1] < map_size[1])
	{

		if (future_player_pos[0] == box_pos[0] && future_player_pos[1] == box_pos[1])
		{
			future_box_pos[0] = (int)box_pos[0] + (future_player_pos[0] - (int)player_pos[0]);
			future_box_pos[1] = (int)box_pos[1] + (future_player_pos[1] - (int)player_pos[1]);

			if (future_box_pos[0] >= 0 && future_box_pos[0] < map_size[0] && future_box_pos[1] >= 0 && future_box_pos[1] < map_size[1])
			{
				grid[player_pos[0]][player_pos[1]] = ' ';
				player_pos[0] = (unsigned short)future_player_pos[0];
				player_pos[1] = (unsigned short)future_player_pos[1];

				box_pos[0] = (unsigned short)future_box_pos[0];
				box_pos[1] = (unsigned short)future_box_pos[1];
			}
		}
		else
		{
#ifdef PULL
			if ((2 * (int)player_pos[0] - future_player_pos[0]) == box_pos[0] && (2 * (int)player_pos[1] - future_player_pos[1]) == box_pos[1])
			{
				grid[box_pos[0]][box_pos[1]] = ' ';
				box_pos[0] = player_pos[0];
				box_pos[1] = player_pos[1];
			}

#endif
			grid[player_pos[0]][player_pos[1]] = ' ';

			player_pos[0] = (unsigned short)future_player_pos[0];
			player_pos[1] = (unsigned short)future_player_pos[1];
		}
	}
	grid[goal_pos[0]][goal_pos[1]] = 'G';
	grid[box_pos[0]][box_pos[1]] = 'B';
	grid[player_pos[0]][player_pos[1]] = 'P';
}

/* Frees the allocated grid memory */
void freeGrid(char **grid, unsigned short map_size[2])
{
	unsigned short i;

	if (grid != NULL)
	{
		for (i = 0; i < map_size[0]; i++)
		{
			free(grid[i]);
		}

		free(grid);
		grid = NULL;
	}
}

/* Determines win/lose status by checking if player can reach goal */
unsigned char winOrLose(char **grid, unsigned short map_size[2], unsigned short box_pos[2], unsigned short goal_pos[2])
{
	unsigned char return_val = 0;

	/* Check if player is at goal position */
	if (memcmp(box_pos, goal_pos, sizeof(unsigned short) * 2) == 0)
	{

		printf("You Win!\n");
		return_val = 1;
	}

#ifndef PULL
	if ((box_pos[0] == 0 || box_pos[0] == map_size[0] - 1) || (box_pos[1] == 0 || box_pos[1] == map_size[1] - 1))
	{
		printf("You Lose!\n");
		return_val = 1; /* Player cannot reach goal */
	}
#endif

	return return_val;
}
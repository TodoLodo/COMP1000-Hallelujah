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

/* Initializes a 2D grid with specified dimensions and places player and goal at given positions */
char **initGrid(unsigned short map_size[2], unsigned short player_pos[2], unsigned short goal_pos[2])
{
	unsigned short row;
	char **grid = (char **)malloc(sizeof(char *) * map_size[0]); /* Allocate rows for grid */

	if (grid != NULL)
	{
		/* Loop through rows, allocate columns, initialize empty spaces */
		for (row = 0; row < map_size[0]; row++)
		{
			grid[row] = (char *)malloc(sizeof(char) * map_size[1]); /* Allocate memory for columns */

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
void printGrid(char **grid, unsigned short map_size[2])
{
	unsigned short i;
	char *h_border = malloc(sizeof(char) * (map_size[1] + 2));
	memset(h_border, '*', map_size[1] + 2);

	system("clear");

	printf("%s\n", h_border);
	for (i = 0; i < map_size[0]; i++)
	{
		printf("*%s*\n", grid[i]);
	}
	printf("%s\n", h_border);

	free(h_border);
}

/* Creates a floor break ('X') at a random unoccupied position on the grid */
void breakFloor(char **grid, unsigned short map_size[2])
{
	unsigned short x_pos[2];
	unsigned char unique = 0;

	/* Find a random empty spot and place an 'X' */
	while (!unique)
	{
		x_pos[0] = random(0, map_size[0] - 1);
		x_pos[1] = random(0, map_size[1] - 1);

		if (grid[x_pos[0]][x_pos[1]] == ' ')
		{
			grid[x_pos[0]][x_pos[1]] = 'X';
			unique = 1;
		}
	}
}

/* Adjusts the position to wrap around borders if BORDERLESS is defined */
void _borderless(int pos[2], unsigned short map_size[2])
{
	if (pos[0] < 0)
	{
		pos[0] = map_size[0] - 1;
	}
	else if (pos[0] >= map_size[0])
	{
		pos[0] = 0;
	}

	if (pos[1] < 0)
	{
		pos[1] = map_size[1] - 1;
	}
	else if (pos[1] >= map_size[1])
	{
		pos[1] = 0;
	}
}

/* Moves the player based on user input and checks border conditions */
void movePlayer(char user_input, char **grid, unsigned short map_size[2], unsigned short player_pos[2])
{
	int future_pos[2];

	future_pos[0] = (int)player_pos[0];
	future_pos[1] = (int)player_pos[1];

	/* Update future position based on input */
	switch (user_input)
	{
	case 'w':
		future_pos[0]--;
		break;

	case 's':
		future_pos[0]++;
		break;

	case 'a':
		future_pos[1]--;
		break;

	case 'd':
		future_pos[1]++;
		break;

	default:
		break;
	}

#ifdef BORDERLESS
	_borderless(future_pos, map_size);
#endif

	/* Move player to future position if accessible */
	if (!(future_pos[0] == (int)player_pos[0] && future_pos[1] == (int)player_pos[1]) && future_pos[0] >= 0 && future_pos[0] < map_size[0] && future_pos[1] >= 0 && future_pos[1] < map_size[1] && grid[future_pos[0]][future_pos[1]] != 'X')
	{
		grid[player_pos[0]][player_pos[1]] = ' ';
		player_pos[0] = (unsigned short)future_pos[0];
		player_pos[1] = (unsigned short)future_pos[1];
		grid[player_pos[0]][player_pos[1]] = 'P';

		breakFloor(grid, map_size);
	}
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

/* Validates the position on grid as accessible and unvisited */
unsigned char _isValid(int pos[2], unsigned char **visited, char **grid, unsigned short map_size[2])
{
	return pos[0] >= 0 && pos[0] < map_size[0] && pos[1] >= 0 && pos[1] < map_size[1] && grid[pos[0]][pos[1]] != 'X' && !visited[pos[0]][pos[1]];
}

/* Recursive DFS algorithm to find path to goal */
unsigned char _dfs(int pos[2], unsigned char **visited, char **grid, unsigned short map_size[2])
{
	unsigned char found_path = 0;
	int newPos[2];

#ifdef BORDERLESS
	_borderless(pos, map_size);
#endif

	/* Validate position */
	if (_isValid(pos, visited, grid, map_size))
	{
		/* Check if goal is reached */
		if (grid[pos[0]][pos[1]] == 'G')
		{
			found_path = 1;
		}
		else
		{
			visited[pos[0]][pos[1]] = 1; /* Mark cell as visited */

			/* Explore all 4 directions */
			/* Up */
			newPos[0] = pos[0] - 1;
			newPos[1] = pos[1];
			found_path = _dfs(newPos, visited, grid, map_size);

			/* Down */
			if (!found_path)
			{
				newPos[0] = pos[0] + 1;
				newPos[1] = pos[1];
				found_path = _dfs(newPos, visited, grid, map_size);
			}

			/* Left */
			if (!found_path)
			{
				newPos[0] = pos[0];
				newPos[1] = pos[1] - 1;
				found_path = _dfs(newPos, visited, grid, map_size);
			}

			/* Right */
			if (!found_path)
			{
				newPos[0] = pos[0];
				newPos[1] = pos[1] + 1;
				found_path = _dfs(newPos, visited, grid, map_size);
			}
		}
	}

	return found_path;
}

/* Determines win/lose status by checking if player can reach goal */
unsigned char winOrLose(char **grid, unsigned short map_size[2], unsigned short player_pos[2], unsigned short goal_pos[2])
{
	unsigned char return_val = 0, **visited = NULL;
	unsigned short i;
	int int_pos[2];

	int_pos[0] = (int)player_pos[0];
	int_pos[1] = (int)player_pos[1];

	visited = (unsigned char **)malloc(sizeof(unsigned char *) * map_size[0]);

	for (i = 0; i < map_size[0]; i++)
	{

		visited[i] = (unsigned char *)malloc(map_size[1]);
		memset(visited[i], 0, map_size[1]);
	}

	/* Check if player is at goal position */
	if (memcmp(player_pos, goal_pos, sizeof(unsigned short) * 2) == 0)
	{

		printf("You Win!\n");
		return_val = 1;
	}
	else if (!_dfs(int_pos, visited, grid, map_size))
	{
		printf("You Lose!\n");
		return_val = 1; /* Player cannot reach goal */
	}

	/* Free memory */
	for (i = 0; i < map_size[0]; i++)
	{
		free(visited[i]);
	}
	free(visited);

	return return_val;
}

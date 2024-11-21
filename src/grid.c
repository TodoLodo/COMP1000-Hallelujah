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
char **initGrid(uint16_t map_size[2], uint16_t player_pos[2], uint16_t goal_pos[2])
{
	uint16_t row;
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
void printGrid(char **grid, uint16_t map_size[2])
{
	uint16_t i;
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
void breakFloor(char **grid, uint16_t map_size[2])
{
	uint16_t x_pos[2];
	uint8_t unique = 0;

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
void _borderless(int32_t pos[2], uint16_t map_size[2])
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
void movePlayer(char user_input, char **grid, uint16_t map_size[2], uint16_t player_pos[2])
{
	int32_t future_pos[2];

	future_pos[0] = (int32_t)player_pos[0];
	future_pos[1] = (int32_t)player_pos[1];

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
	if (!(future_pos[0] == (int32_t)player_pos[0] && future_pos[1] == (int32_t)player_pos[1]) && future_pos[0] >= 0 && future_pos[0] < map_size[0] && future_pos[1] >= 0 && future_pos[1] < map_size[1] && grid[future_pos[0]][future_pos[1]] != 'X')
	{
		grid[player_pos[0]][player_pos[1]] = ' ';
		player_pos[0] = (uint16_t)future_pos[0];
		player_pos[1] = (uint16_t)future_pos[1];
		grid[player_pos[0]][player_pos[1]] = 'P';

		breakFloor(grid, map_size);
	}
}

/* Frees the allocated grid memory */
void freeGrid(char **grid, uint16_t map_size[2])
{
	uint16_t i;

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
uint8_t _isValid(int32_t pos[2], uint8_t **visited, char **grid, uint16_t map_size[2])
{
	return pos[0] >= 0 && pos[0] < map_size[0] && pos[1] >= 0 && pos[1] < map_size[1] && grid[pos[0]][pos[1]] != 'X' && !visited[pos[0]][pos[1]];
}

/* Recursive DFS algorithm to find path to goal */
uint8_t _dfs(int32_t pos[2], uint8_t **visited, char **grid, uint16_t map_size[2])
{
	uint8_t found_path = 0;
	int32_t newPos[2];

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
uint8_t winOrLose(char **grid, uint16_t map_size[2], uint16_t player_pos[2], uint16_t goal_pos[2])
{
	uint8_t return_val = 0, **visited = NULL;
	uint16_t i;
	int32_t int_pos[2];

	int_pos[0] = (int32_t)player_pos[0];
	int_pos[1] = (int32_t)player_pos[1];

	visited = (uint8_t **)malloc(sizeof(uint8_t *) * map_size[0]);

	for (i = 0; i < map_size[0]; i++)
	{

		visited[i] = (uint8_t *)malloc(map_size[1]);
		memset(visited[i], 0, map_size[1]);
	}

	/* Check if player is at goal position */
	if (memcmp(player_pos, goal_pos, sizeof(uint16_t) * 2) == 0)
	{
		return_val = 1;
	}
	else if (!_dfs(int_pos, visited, grid, map_size))
	{
		return_val = 2; /* Player cannot reach goal */
	}

	/* Free memory */
	for (i = 0; i < map_size[0]; i++)
	{
		free(visited[i]);
	}
	free(visited);

	return return_val;
}

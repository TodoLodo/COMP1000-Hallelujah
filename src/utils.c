/*
	*******
	* P X *
	*   G *
	*******

	Filename: util.c
	Description: Utility functions for command-line argument parsing and user input
	Author: Todo Lodo
*/

#include "utils.h"

/* Parses command-line arguments to initialize map size, player position, and goal position */
uint8_t argParser(int argc, char **argv, uint16_t map_size[2], uint16_t player_pos[2], uint16_t goal_pos[2])
{
	uint8_t return_val = 1;
	char *endptr; /* Pointer to track any invalid characters during conversion */

	/* Check if the correct number of arguments are provided */
	if (argc != 7) /* Expecting 6 arguments (7 including program name) */
	{
		printf("Error: Invalid number of arguments!\n");
		return_val = 0;
	}
	else
	{
		/* Parse map rows */
		map_size[0] = (uint16_t)strtoul(argv[1], &endptr, 10);
		if (*endptr != '\0')
		{
			printf("Error: Invalid argument for map rows, %s\n", endptr);
			return return_val = 0;
		}

		/* Parse map columns */
		map_size[1] = (uint16_t)strtoul(argv[2], &endptr, 10);
		if (*endptr != '\0')
		{
			printf("Error: Invalid argument for map columns, %s\n", endptr);
			return return_val = 0;
		}

		/* Parse player row */
		player_pos[0] = (uint16_t)strtoul(argv[3], &endptr, 10);
		if (*endptr != '\0')
		{
			printf("Error: Invalid argument for player row, %s\n", endptr);
			return return_val = 0;
		}

		/* Parse player column */
		player_pos[1] = (uint16_t)strtoul(argv[4], &endptr, 10);
		if (*endptr != '\0')
		{
			printf("Error: Invalid argument for player column, %s\n", endptr);
			return return_val = 0;
		}

		/* Parse goal row */
		goal_pos[0] = (uint16_t)strtoul(argv[5], &endptr, 10);
		if (*endptr != '\0')
		{
			printf("Error: Invalid argument for goal row, %s\n", endptr);
			return return_val = 0;
		}

		/* Parse goal column */
		goal_pos[1] = (uint16_t)strtoul(argv[6], &endptr, 10);
		if (*endptr != '\0')
		{
			printf("Error: Invalid argument for goal column, %s\n", endptr);
			return return_val = 0;
		}

		/* Check if the parsed values are within valid range */
		if (return_val)
		{
			/* Validate player position within map bounds */
			if (player_pos[0] >= map_size[0] || player_pos[1] >= map_size[1])
			{
				printf("Error: Player is out of bounds!\n");
				return_val = 0;
			}

			/* Validate goal position within map bounds */
			if (goal_pos[0] >= map_size[0] || goal_pos[1] >= map_size[1])
			{
				printf("Error: Goal is out of bounds!\n");
				return_val = 0;
			}

			/* Ensure player and goal positions are not the same */
			if (return_val && (memcmp(player_pos, goal_pos, sizeof(uint16_t) * 2) == 0))
			{
				printf("Error: Player and Goal positions can't be the same!\n");
				return_val = 0;
			}
		}
	}

	return return_val;
}

/* Captures user input for directional movement */
char getUserInput()
{
	char input;

	/* Prompt the user for movement input */
	printf("Press w to go up\nPress s to go down\nPress a to go left\nPress d to go right\n");

	/* Temporarily disable input buffering to read single character input */
	disableBuffer();
	scanf(" %c", &input);
	enableBuffer();

	return input;
}

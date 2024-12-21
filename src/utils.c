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
unsigned char argParser(int argc, char **argv, unsigned short map_size[2], unsigned short player_pos[2], unsigned short goal_pos[2])
{
	unsigned char return_val = 1;
	int tmp_val; /* Temporary variable for parsing */
	char *endptr;	 /* Pointer to track any invalid characters during conversion */

	/* Check if the correct number of arguments are provided */
	if (argc != 7) /* Expecting 6 arguments (7 including program name) */
	{
		printf("Error: Invalid number of arguments!\n");
		return_val = 0;
	}
	else
	{
		/* Parse map rows */
		tmp_val = strtol(argv[1], &endptr, 10);
		if (*endptr != '\0') /* Check for invalid characters */
		{
			printf("Error: Invalid argument for map rows, %s\n", endptr);
			return_val = 0;
		}
		if (tmp_val < 5) /* Check if negative */
		{
			printf("Error: Map rows cannot be less than 5!\n");
			return_val = 0;
		}
		map_size[0] = (unsigned short)tmp_val;

		/* Parse map columns */
		tmp_val = strtol(argv[2], &endptr, 10);
		if (*endptr != '\0') /* Check for invalid characters */
		{
			printf("Error: Invalid argument for map columns, %s\n", endptr);
			return_val = 0;
		}
		if (tmp_val < 5) /* Check if negative */
		{
			printf("Error: Map columns cannot be less than 5!\n");
			return_val = 0;
		}
		map_size[1] = (unsigned short)tmp_val;

		/* Parse player row */
		tmp_val = strtol(argv[3], &endptr, 10);
		if (*endptr != '\0') /* Check for invalid characters */
		{
			printf("Error: Invalid argument for player row, %s\n", endptr);
			return_val = 0;
		}
		if (tmp_val < 0) /* Check if negative */
		{
			printf("Error: Player row cannot be negative!\n");
			return_val = 0;
		}
		player_pos[0] = (unsigned short)tmp_val;

		/* Parse player column */
		tmp_val = strtol(argv[4], &endptr, 10);
		if (*endptr != '\0') /* Check for invalid characters */
		{
			printf("Error: Invalid argument for player column, %s\n", endptr);
			return_val = 0;
		}
		if (tmp_val < 0) /* Check if negative */
		{
			printf("Error: Player column cannot be negative!\n");
			return_val = 0;
		}
		player_pos[1] = (unsigned short)tmp_val;

		/* Parse goal row */
		tmp_val = strtol(argv[5], &endptr, 10);
		if (*endptr != '\0') /* Check for invalid characters */
		{
			printf("Error: Invalid argument for goal row, %s\n", endptr);
			return_val = 0;
		}
		if (tmp_val < 0) /* Check if negative */
		{
			printf("Error: Goal row cannot be negative!\n");
			return_val = 0;
		}
		goal_pos[0] = (unsigned short)tmp_val;

		/* Parse goal column */
		tmp_val = strtol(argv[6], &endptr, 10);
		if (*endptr != '\0') /* Check for invalid characters */
		{
			printf("Error: Invalid argument for goal column, %s\n", endptr);
			return_val = 0;
		}
		if (tmp_val < 0) /* Check if negative */
		{
			printf("Error: Goal column cannot be negative!\n");
			return_val = 0;
		}
		goal_pos[1] = (unsigned short)tmp_val;

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
			if (return_val && (memcmp(player_pos, goal_pos, sizeof(unsigned short) * 2) == 0))
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

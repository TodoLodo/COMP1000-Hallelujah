/*
	*******
	* P X *
	* t G *
	*******

	Filename: test_utils.c
	Description: Unit tests for the argParser function in utils.c
	Author: Todo Lodo
*/

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

extern uint8_t argParser(int argc, char **argv, uint16_t map_size[2], uint16_t player_pos[2], uint16_t goal_pos[2]);

void test_argParser(void)
{
	uint16_t map_size[2];
	uint16_t player_pos[2];
	uint16_t goal_pos[2];

	/* Test case 1: Valid input */
	{
		char *args1[] = {"program", "10", "10", "2", "5", "3", "4"};
		assert(argParser(7, args1, map_size, player_pos, goal_pos) == 1);
		assert(map_size[0] == 10 && map_size[1] == 10);
		assert(player_pos[0] == 2 && player_pos[1] == 5);
		assert(goal_pos[0] == 3 && goal_pos[1] == 4);
	}

	/* Test case 2: Invalid number of arguments */
	{
		char *args2[] = {"program", "10", "10", "2", "5", "3"};
		assert(argParser(6, args2, map_size, player_pos, goal_pos) == 0);
	}

	/* Test case 3: Negative map rows */
	{
		char *args3[] = {"program", "-10", "10", "2", "5", "3", "4"};
		assert(argParser(7, args3, map_size, player_pos, goal_pos) == 0);
	}

	/* Test case 4: Invalid argument for map columns */
	{
		char *args4[] = {"program", "10", "abc", "2", "5", "3", "4"};
		assert(argParser(7, args4, map_size, player_pos, goal_pos) == 0);
	}

	/* Test case 5: Player out of bounds */
	{
		char *args5[] = {"program", "10", "10", "10", "5", "3", "4"};
		assert(argParser(7, args5, map_size, player_pos, goal_pos) == 0);
	}

	/* Test case 6: Player and Goal positions are the same */
	{
		char *args6[] = {"program", "10", "10", "3", "4", "3", "4"};
		assert(argParser(7, args6, map_size, player_pos, goal_pos) == 0);
	}

	printf("All argParser tests passed!\n");
}

int main(void)
{
	test_argParser();
	return 0;
}

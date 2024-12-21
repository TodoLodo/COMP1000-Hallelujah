/*
	*******
	* P X *
	* t G *
	*******

	Filename: test_grid.c
	Description: Unit tests for grid functions in grid.c
	Author: Todo Lodo
*/

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

extern char **initGrid(uint16_t map_size[2], uint16_t player_pos[2], uint16_t goal_pos[2]);
extern void movePlayer(char user_input, char **grid, uint16_t map_size[2], uint16_t player_pos[2]);
extern uint8_t winOrLose(char **grid, uint16_t map_size[2], uint16_t player_pos[2], uint16_t goal_pos[2]);
extern void freeGrid(char **grid, uint16_t map_size[2]);

void test_initGrid(void)
{
	uint16_t map_size[2] = {5, 5};
	uint16_t player_pos[2] = {2, 2};
	uint16_t goal_pos[2] = {3, 3};

	char **grid = initGrid(map_size, player_pos, goal_pos);
	assert(grid != NULL);
	assert(grid[2][2] == 'P'); /* Check if player is placed correctly */
	assert(grid[3][3] == 'G'); /* Check if goal is placed correctly */
	assert(grid[0][0] == ' '); /* Ensure the rest of the grid is empty */
	freeGrid(grid, map_size);
}

void test_movePlayer(void)
{
	uint16_t map_size[2] = {5, 5};
	uint16_t player_pos[2] = {2, 2};
	uint16_t goal_pos[2] = {3, 3};
	char **grid = initGrid(map_size, player_pos, goal_pos);

	movePlayer('s', grid, map_size, player_pos);	  /* Move down */
	assert(player_pos[0] == 3 && player_pos[1] == 2); /* Player should move down */

	movePlayer('d', grid, map_size, player_pos);	  /* Move right */
	assert(player_pos[0] == 3 && player_pos[1] == 3); /* Player should move to goal */

	movePlayer('w', grid, map_size, player_pos);	  /* Move up */
	assert(player_pos[0] == 2 && player_pos[1] == 3); /* Player should move up */

	freeGrid(grid, map_size);
}

void test_winOrLose(void)
{
	uint16_t map_size[2] = {5, 5};
	uint16_t player_pos[2] = {2, 3};
	uint16_t goal_pos[2] = {3, 3};
	char **grid = initGrid(map_size, player_pos, goal_pos);

	assert(winOrLose(grid, map_size, player_pos, goal_pos) == 0); /* Player not at goal */

	movePlayer('s', grid, map_size, player_pos);				  /* Move down to goal */
	assert(winOrLose(grid, map_size, player_pos, goal_pos) == 1); /* Player at goal */

	freeGrid(grid, map_size);
}

int main(void)
{
	test_initGrid();
	test_movePlayer();
	test_winOrLose();

	printf("All grid tests passed!\n");
	return 0;
}

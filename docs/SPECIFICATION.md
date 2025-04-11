# Assignment Specification

## Objectives:

1. **Command Line Arguments**: The executable should be called `escape` and accept six command line parameters:

    ```bash
    ./escape <row_map> <col_map> <row_player> <col_player> <row_goal> <col_goal>
    ```

    - Validate the input to ensure proper data types and acceptable ranges.
    - Handle errors related to argument count and invalid values gracefully without using the `exit()` function.

2. **Map Interface**: Upon running the program, it should:

    - Clear the terminal screen.
    - Print a 2D map showing the player and goal positions, using specific characters for representation:
        - `*` for map borders.
        - `P` for the player location.
        - `G` for the goal location.
        - `X` for collapsed floor grids.

3. **User Input**: Implement functionality for user movement commands:

    - Accept single-character commands (`w`, `a`, `s`, `d`) for movement.
    - Ignore invalid inputs and provide warning messages.
    - Ensure the player cannot move into borders or collapsed areas.

4. **Randomized Collapsing Floor**: Implement a feature where the floor grid collapses randomly after each player movement, ensuring it does not collapse on the player or goal.

5. **Win/Lose Conditions**: Define the game end conditions:

    - Win when the player reaches the goal.
    - Lose if the player or goal becomes trapped by collapsed floors.

6. **Conditional Compilation**: Implement a BORDERLESS feature to allow the player to traverse to the other end of the map when compiled with `BORDERLESS` defined.

## Additional Requirements:

### Makefile:

Create a manually written Makefile with:

-   Proper structure, variables, flags, targets, and prerequisites.
-   Clean rule for cleaning up generated files.

## Assumptions:

-   User input will be valid for data types.
-   Reasonable map sizes will be used (not excessively large).
-   Only lowercase inputs will be handled.

## Marking Criteria:

-   Properly structured Makefile (5 marks).
-   Successful compilation and execution without crashes (5 marks).
-   Usage of header guards and sufficient in-code commenting (2 marks).
-   Readability and framework of the program, including multiple files (3 marks).
-   Adherence to coding standards (5 marks).
-   No memory leaks (10 marks).
-   Functionalities as outlined (total of 50 marks).

For more information about this assignment, please refer to the [Assignment Details PDF](/UCP_2022_S2_Assignment_1.pdf).

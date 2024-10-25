# COMP1000: Assignment 1 - Semester 2, 2022

## Assignment Explanation

## Overview

This assignment involves developing a C program that implements a simple game to be played in the Linux terminal.

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

## Initial Setup

You can either **download the assignment** or **clone the repository**:

1. **Download the ZIP file** of this assignment from GitHub:

    - [Download Assignment 1](https://github.com/todolodo/COMP1000/archive/refs/heads/2022-S2-A1.zip)

2. **Alternatively, clone the repository** and directly check out this assignment branch:
    ```bash
    git clone -b 2022-S2-A1 https://github.com/todolodo/COMP1000.git
    ```

## User Guide

### Building the Program

To compile the source files, use the following command in the terminal to build using the rules in the `Makefile`:

```bash
make
```

To compile with the **BORDERLESS** condition, use the following command:

```bash
make BORDERLESS=1
```

### Running the Program

Once the program is compiled, you can run it with command-line arguments as follows:

```bash
./escape <row_map> <col_map> <row_player> <col_player> <row_goal> <col_goal>
```

- `row_map`: Number of rows in the map.
- `col_map`: Number of columns in the map.
- `row_player`: Player's row position.
- `col_player`: Player's column position.
- `row_goal`: Goal's row position.
- `col_goal`: Goal's column position.

### Player Controls

Once the game is running, you can control the player using the following commands:

- **`w`**: Move the player one block up.
- **`s`**: Move the player one block down.
- **`a`**: Move the player one block left.
- **`d`**: Move the player one block right.

#### Control Mechanics

- The player can only move into empty spaces (denoted by spaces on the map). If the player tries to move into a border (unless build with BORDERLESS condition player will warp to the otherside if empty) or a collapsed area (denoted by 'X'), the move will not be executed, and the player will remain in their current position.
- Invalid inputs will be ignored, and you may receive a warning message like "Invalid key" for unrecognized commands.



### Example

To create a map with 20 rows and 30 columns, with the player starting at position (2, 5) and the goal located at (10, 14), use the following command:

```bash
./escape 20 30 2 5 10 14
```

Initially, the program will display the following output:

![Local Image](/images/output.jpg)

### Error Handling

If any issues occur, such as a missing input file, the program will return an error like:

```
Error: Could not open input.txt
```

### Testing

You can run tests by executing:

```bash
make test
```

Or manually run the test binary:

```bash
./tests/test_assignment1
```

---

## Back to Main Branch

To view the main repository or switch to the main branch, use the link below:

-   [Go to Main Branch](https://github.com/todolodo/COMP1000/tree/main)

# COMP1000: Assignment 1 - Semester 2, 2022

## Overview

This assignment involves developing a C program that implements a simple game to be played in the Linux terminal.

## Initial Setup

You can either **download the assignment** or **clone the repository**:

1. **Download the ZIP file** of this assignment from GitHub:

    - [Download Source Archive](https://github.com/todolodo/COMP1000/archive/refs/heads/2022-S2-A1.zip)

2. Alternatively, **clone the repository** and directly check out this assignment branch:
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
./bin/escape <row_map> <col_map> <row_player> <col_player> <row_goal> <col_goal>
```

-   `row_map`: Number of rows in the map.
-   `col_map`: Number of columns in the map.
-   `row_player`: Player's row position.
-   `col_player`: Player's column position.
-   `row_goal`: Goal's row position.
-   `col_goal`: Goal's column position.

### Player Controls

Once the game is running, you can control the player using the following commands:

-   **`w`**: Move the player one block up.
-   **`s`**: Move the player one block down.
-   **`a`**: Move the player one block left.
-   **`d`**: Move the player one block right.

#### Control Mechanics

-   The player can only move into empty spaces (denoted by spaces on the map). If the player tries to move into a border (unless build with BORDERLESS condition player will warp to the otherside if empty) or a collapsed area (denoted by 'X'), the move will not be executed, and the player will remain in their current position.
-   Invalid inputs will be ignored, and you may receive a warning message like "Invalid key" for unrecognized commands.

### Example

To create a map with 20 rows and 30 columns, with the player starting at position (2, 5) and the goal located at (10, 14), use the following command:

```bash
./bin/escape 20 30 2 5 10 14
```

Initially, the program will display the following output:

![Local Image](/images/output.jpg)

### Error Handling

During the execution of the program, various issues may arise, and appropriate error messages will be displayed. Below are examples of potential error prompts you might encounter:

1. **Invalid Number of Arguments**: The program requires exactly 6 command line arguments. If the correct number is not provided, the following error will appear:

    ```
    Error: Invalid number of arguments!
    ```

2. **Invalid Argument Format**: If the program receives the correct number of arguments but encounters issues during parsing, one or more of the following prompts may appear:

    ```
    Error: Invalid argument for map rows, <specific_argument>
    ```

    ```
    Error: Invalid argument for map columns, <specific_argument>
    ```

    ```
    Error: Invalid argument for player row, <specific_argument>
    ```

    ```
    Error: Invalid argument for player column, <specific_argument>
    ```

    ```
    Error: Invalid argument for goal row, <specific_argument>
    ```

    ```
    Error: Invalid argument for goal column, <specific_argument>
    ```

3. **Invalid Argument Value**: If a provided argument is negative for position arguments or less than the minimum required for map size arguments, the following prompts will appear:

    ```
    Error: Map rows cannot be less than 5!
    ```

    ```
    Error: Map columns cannot be less than 5!
    ```

    ```
    Error: Player row cannot be negative!
    ```

    ```
    Error: Player column cannot be negative!
    ```

    ```
    Error: Goal row cannot be negative!
    ```

    ```
    Error: Goal column cannot be negative!
    ```

4. **Out of Boundaries**: If any positional argument falls outside the defined map size, the following error messages will appear:

    ```
    Error: Player is out of bounds!
    ```

    ```
    Error: Goal is out of bounds!
    ```

5. **Identical Positional Arguments**: If the goal position is the same as the player position, the following message will be displayed:

    ```
    Error: Player and Goal positions can't be the same!
    ```

### Testing

You can run tests by executing:

```bash
make test
```

Or specific testing for utils or/and grid functionalities as follows:

```bash
make test_utils
```

```bash
make test_grid
```


---

## Back to Main Branch

To view the main repository or switch to the main branch, use the link below:

-   [Go to Main Branch](https://github.com/todolodo/COMP1000/tree/main)

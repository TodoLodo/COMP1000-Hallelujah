# Mighty Explanation

## Table of Contents
1. [Project Directory Structure](#1-project-directory-structure)
2. [Approach and Logic](#2-approach-and-logic)
3. [Pre-thinking and Design Decisions](#3-pre-thinking-and-design-decisions)
4. [Step-by-Step Logical Flow](#4-step-by-step-logical-flow)
5. [Make it. Run it. Done.](#5-)

---

## 1. Project Directory Structure

The directory structure follows standard practices for organizing C projects, ensuring maintainability, clarity, and scalability. Here's the detailed breakdown:

```
[Project Dir]
│
├─── bin            # Compiled binaries and executables
├─── build          # Temporary files generated during the build process
├─── docs           # Documentation files, such as EXPLANATION.md and README.md
├─── images         # Any image assets, such as diagrams or screenshots for documentation
├─── include        # Header files (.h) that declare functions, macros, and data structures
├─── lib            # Provided `.h` and `.c` files from the assignment or other library code
├─── src            # Source files (.c) implementing project-specific functionality
└─── tests          # Test cases for verifying the project's correctness
```


### Purpose of Each Folder

- **bin**
    - Stores the compiled executables or binaries after the build process.
    - Keeps the main project directory clean by separating build artifacts from source code.

- **build**
    - Temporary build files generated during the compilation process, such as object files (`.o`) and dependency files.
    - Helps maintain a clear distinction between source code and intermediary compilation outputs.

- **docs**
    - Includes all project documentation files, such as:
        - `EXPLANATION.md`: A deep dive into the project's design and logic.
        - `SPECIFICATION.md`: An overview of the project with instructions for setup and usage.
    - Can also store additional files like design documents or external references.

- **images**
    - Houses visual assets like diagrams, flowcharts, or screenshots used in documentation.
    - Useful for illustrating key concepts or providing visual aids for users.

- **include**
    - Contains all the header files (`.h`) used in the project.
    - Promotes modularity by allowing function declarations, macro definitions, and data structure declarations to be easily shared across multiple source files.

- **lib**
    - Stores external or provided library code, including `.h` and `.c` files given as part of the assignment.
    - Keeps the project modular and organized by isolating reusable components.

- **src**
    - The main directory for source code files (`.c`) that implement the core functionality of the project.
    - Typically contains implementation code specific to your project objectives.

- **tests**
    - Contains test cases to verify the functionality and correctness of the code.
    - May include unit tests, integration tests, or scripts to automate the testing process.

### Why This Structure?
This structure:
- Follows a logical hierarchy that separates concerns (source, headers, tests, etc.).
- Facilitates easier navigation and understanding for contributors.
- Aligns with widely accepted standards, making it easier for others to contribute or review your work.

---

## 2. Approach and Logic

### **Objective**

The main goal of this program is to create an interactive terminal-based game called **escape**. The key functionalities are:

1. Accept and validate command-line arguments to configure the game environment.
2. Render a 2D map dynamically, showing the player's position, the goal, and collapsing floor grids.
3. Respond to user input for player movement, ensuring boundary and obstacle constraints are adhered to.
4. Randomize floor collapses to introduce unpredictability, making the game engaging.
5. Implement winning and losing conditions, ending the game based on player actions and map state.
6. Add a **BORDERLESS** compilation option to allow advanced movement across map edges.

### Key Challenges and Solutions

#### Command-Line Argument Parsing
- **Challenge**: Validate six numerical inputs for rows, columns, and positions for the player and goal.
- **Solution**:  
  - Use `argc` and `argv` to check for the exact number of arguments.
  - Parse inputs using `atoi()`, ensuring proper integer conversion and range checks.
  - Handle invalid input gracefully with error messages and a loop prompting for corrections, avoiding abrupt program termination via `exit()`.

#### Map Interface Rendering
- **Challenge**: Dynamically display a 2D grid that updates after each player movement.
- **Solution**:  
  - Use `*` for borders, `P` for the player, `G` for the goal, and `X` for collapsed grids.
  - Clear the terminal screen with `system("clear")` (Unix) before re-rendering the updated map.
  - Implement functions to generate the map, place the player and goal, and update the map after each turn.

#### User Input and Movement
- **Challenge**: Process valid movement commands while ignoring invalid ones, ensuring the player cannot move into borders or collapsed grids.
- **Solution**:  
  - Use `scanf()` to read user input.
  - Map movement commands (`w`, `a`, `s`, `d`) to directional changes in the player's coordinates.
  - Check boundaries and prevent illegal movements with conditional statements.

#### Randomized Collapsing Floor
- **Challenge**: Randomly collapse a floor grid after each movement, avoiding the player and goal positions.
- **Solution**:  
  - Use a random number generator to select a non-collapsed grid position.
  - Ensure the chosen position does not overlap with the player or goal by validating against their coordinates.
  - Update the grid state with `X` for collapsed tiles.

#### Win/Lose Conditions
- **Challenge**: Detect when the player has won or lost.
- **Solution**:  
  - Win Condition: Check if the player's position matches the goal's coordinates after a move.
  - Lose Condition: Determine if all paths to the goal are blocked by collapsed grids, trapping the player or goal.

#### Conditional Compilation with BORDERLESS
- **Challenge**: Allow the player to wrap around the map edges when the `BORDERLESS` feature is defined during compilation.
- **Solution**:  
  - Use preprocessor directives (`#ifdef BORDERLESS`) to enable or disable this feature.
  - Implement logic to move the player to the opposite edge when they exceed the map boundaries.

### Solution Overview

This program integrates modular functions for each component, enabling a clear and maintainable structure. Key functions include:

1. **`argParser()`**: Parses and validates command-line arguments.
2. **`printGrid()`**: Dynamically prints the map with current states of the player, goal, and collapsed grids.
3. **`getUserInput()`**: Handles user movement commands and updates the player's position.
4. **`breakFloor()`**: Randomly collapses a floor grid after each player movement.
5. **`winOrLose()`**: Determines the game's end condition based on the player's actions and map state.

---

## 3. Pre-thinking and Design Decisions

### a. Structuring Code into Multiple Files
- **Reasoning**:  
  - To maintain readability and modularity, the main function should act as the central hub, only responsible for calling other structured code. It should not be overloaded with implementation details.
  - By splitting the code into multiple files, each dedicated to a specific responsibility, it becomes easier to manage, debug, and extend. This also aligns with the assignment criterion of having more than one or two `.c` files.
- **Implementation**:  
  - **`grid.c`**: Handles player movement, grid manipulations, and rendering functionalities. All grid-related operations will be contained here for logical grouping.
  - **`utils.c`**: Manages command-line argument parsing, validation, and user input handling. Keeping utility functions separate improves clarity and avoids clutter in other files.
  - **`main.c`**: Contains the main function, the central loop, and declarations for shared variables. This file serves as the entry point for the program, providing a clear distinction of purpose.

### b. Logical Grouping of Related Data
- **Reasoning**:  
  - Although map rows, columns, player positions, and goal positions are given as separate command-line arguments, grouping them logically into arrays provides a more structured way to handle related data.
  - Arrays in C behave as memory pointers, simplifying function calls and value updates without needing to pass multiple separate variables.
- **Implementation**:  
  - **`map_size[2]`**: Stores the number of rows and columns of the map.
  - **`player_pos[2]`** and **`goal_pos[2]`**: Hold the row and column coordinates of the player and goal respectively.

### c. Optimizing Memory Usage with Data Types
- **Reasoning**:  
  - The assignment specifies constraints on the map size, indicating that values will not exceed a 16-bit integer. Additionally, negative values are irrelevant for these variables.
  - Using `unsigned short` (16-bit) instead of `int` (32-bit) helps reduce memory consumption while ensuring the values fall within the expected range. The unsigned modifier ensures no negative values are possible, making the code more precise and efficient.
- **Implementation**:  
  - **`unsigned short`** (equivalent to `uint16_t` in C99+): Used for `map_size`, `player_pos`, and `goal_pos` to minimize memory usage while meeting the program's requirements.

### d. Main Loop and Termination Handling
- **Reasoning**:  
  - Since the assignment prohibits the use of `exit()` or returning from the main function to terminate the program, the win or lose condition will be used to control the main loop.
- **Implementation**:  
  - **`winOrLose`**: The `winOrLose` function will return 1 if a win or lose condition is met, and 0 to continue the game. This return value will be used in the `while` loop condition, so when the condition is met, the loop will terminate, stopping the game.

### e. Grid Representation
- **Reasoning**:  
  - The grid is the program's central element, representing the player, goal, borders, and collapsed floors. Using a 2D array of `char` simplifies visualization and ensures each element requires only 8 bits of memory.
  - Characters (`*`, `P`, `G`, `X`, and spaces) provide a straightforward way to represent the grid visually.
- **Implementation**:  
  - **`char **grid`**: The 2D array holds the current state of the map. The size is determined by the command line arguments passed.

### f. Naming Conventions
- **Reasoning**:  
  - File and variable names should clearly reflect their purpose. This makes the code easier to understand and navigate.
- **Implementation**:  
  - Files like `grid.c`, `utils.c`, and `main.c` are named based on their responsibilities, making it intuitive to locate functions and logic.
  - Variable names such as `map_size`, `player_pos`, and `goal_pos` are chosen for clarity and ease of understanding.
  - **Naming conventions**:
    - **Source files**: Lowercase naming (`grid.c`, `utils.c`, `main.c`).
    - **Global variables/macros**: Uppercase naming (e.g., `MAX_SIZE`, `GAME_RUNNING`).
    - **Function names**: Camel case (`initGrid`, `movePlayer`).
    - **Function parameters/local variables**: Snake case (`player_pos`, `map_size`, `goal_pos`).


---

## 4. Step-by-Step Logical Flow  

### i. Including Necessary Headers  
At the beginning of `main.c`, the following headers are included to access essential functions and maintain modularity:  
```c  
#include "utils.h"  
#include "grid.h"  
#include "random.h"  
```  
- **Purpose**:  
  - `utils.h`: Contains functions for parsing and validating command-line arguments and handling user input.  
  - `grid.h`: Includes all grid-related functions like rendering, player movement, and grid manipulations.  
  - `random.h`: Used to handle randomness, such as collapsing floor tiles in the game grid.  

Refer to the respective files in the **`src`** directory and their declarations in the **`include`** directory for the detailed implementation.  

---

### ii. Declaring the Main Function  
The `main` function is defined with the following parameters:  
```c  
int main(int argc, char **argv)  
```  
- **Purpose**:  
  - `argc`: The count of arguments passed via the command line, including the program name.  
  - `argv`: An array of strings (character pointers) that holds the actual arguments.  

This setup allows the program to dynamically read and process input from the user during execution.  

---

### iii. Declaring Key Variables  
Inside the `main` function, the following variables are declared:  
```c   
unsigned short map_size[2], player_pos[2], goal_pos[2];  /* Map dimensions and player/goal positions */  
char **grid = NULL;                                     /* Grid representation */  
```  

#### Variable Explanation  

##### `map_size`, `player_pos`, and `goal_pos`
- **Purpose**:  
  - These variables hold pairs of related data:  
    - `map_size`: The number of rows and columns of the game map.  
    - `player_pos`: The player's current row and column coordinates.  
    - `goal_pos`: The goal's row and column coordinates.  

- **Data Type Selection**:  
  - `unsigned short` is chosen for efficiency:  
    - It avoids negative values (since positions and map sizes are inherently non-negative).  
    - Its 16-bit size is sufficient for the assignment's constraints on map dimensions.  

- **Usage**:  
  - These variables will be updated after command-line arguments are validated and parsed.  

##### `grid`
- **Purpose**:  
  - Represents the 2D map, which visually displays the game elements, including:  
    - Player position (`P`)  
    - Goal position (`G`)  
    - Collapsed floors (`X`)  
    - Empty floors (` `) 
    - Borders (`*`)  
  - The `grid` variable is dynamically allocated based on the validated map size.  

- **Data Type Selection**:  
  - `char **`: Chosen for a 2D array representation.  
  - Each element is a single character, making it memory-efficient and simple to manage.  

- **Usage**:  
  - The `grid` will be initialized to represent the map's state and updated during the game loop to reflect player movements and collapsing floors.  

#### Design Rationale
- Using these carefully chosen data types and variable names ensures the program is both memory-efficient and easy to understand.  
- Grouping related data into arrays (`map_size`, `player_pos`, `goal_pos`) simplifies parameter passing and updates across functions.  
- Avoiding hardcoding the grid size allows flexibility for different map dimensions provided via command-line arguments.  

---

### iv. Parsing and Validating Command-Line Arguments

After declaring shared variables, the `main` function proceeds with parsing and validating command-line arguments by calling the following function:  

```c
/* Parse and validate arguments, initialize map and player positions */
if (argParser(argc, argv, map_size, player_pos, goal_pos)) {
    ...
}
```

#### Function Overview

The function is declared in `utils.h` as follows:  
```c
unsigned char argParser(int argc, char **argv, unsigned short map_size[2], unsigned short player_pos[2], unsigned short goal_pos[2]);
```  

#### Parameters Explained
1. **`argc` and `argv`**  
   - Passed directly from the `main` function.  
   - `argc`: The number of command-line arguments.  
   - `argv`: An array of strings containing the arguments.  

2. **`map_size[2]`, `player_pos[2]`, `goal_pos[2]`**  
   - Arrays to hold:  
     - `map_size`: The number of rows and columns of the map.  
     - `player_pos`: The initial row and column of the player.  
     - `goal_pos`: The fixed row and column of the goal.  
   - Arrays are passed by reference in C, meaning the function can directly update their values.  


#### What the Function Does
1. **Parses Command-Line Arguments**  
   - Extracts the values of map dimensions, player position, and goal position from the `argv` array.  

2. **Validates Arguments**  
   - Ensures that:  
     - All required arguments are present.  
     - Arguments are of the correct type (e.g., positive integers).  
     - Arguments fall within acceptable ranges.  
   - Handles errors related to argument count and invalid values.  

3. **Updates Shared Variables**  
   - Updates the values of `map_size`, `player_pos`, and `goal_pos` based on the validated arguments.  

4. **Returns Success or Failure**  
   - Returns `1` (true) if all arguments are valid.  
   - Returns `0` (false) if any validation fails.  

#### Key Design Decision

**Why Use Arrays for Data Pairs?**  
- Arrays in C work as memory pointers.  
- Passing an array does not copy its values but provides the function with access to the array's base memory address.  
- This allows efficient updates to the original array elements within the function, simplifying code and avoiding the overhead of copying data.  

**Error Handling**
- Errors are handled gracefully by printing appropriate error messages without exiting the program.  

#### Looking Ahead
To fully understand the functionality of `argParser`, the next step is to analyze its **definition** in `utils.c`.  

---

### v. Parsing and Validating Arguments (Detailed Explanation)

Within `utils.c`, the `argParser` function defines the core logic to parse and validate command-line arguments. Here's a detailed breakdown of its implementation.  

---

#### Variable Declaration

```c
unsigned char return_val = 1;
int tmp_val;        /* Temporary variable for parsing */
char *endptr;       /* Pointer to track invalid characters during conversion */
```

1. **`return_val`**:  
   - Initialized to `1` (success).  
   - Used to indicate whether parsing and validation are successful (1) or not (0).  
   - Avoids multiple `return` statements, improving readability and maintainability.

2. **`tmp_val`**:  
   - A temporary signed integer to store intermediate parsed values.  
   - Using a signed type ensures we can catch negative input values before casting to `unsigned short`.  

3. **`endptr`**:  
   - Tracks invalid characters during conversions using `strtol`.  
   - Essential for error handling when parsing strings to numbers.  

---

#### Step 1: Checking Argument Count

```c
if (argc != 7) /* Expecting 6 arguments (7 including program name) */
{
    printf("Error: Invalid number of arguments!\n");
    return_val = 0;
}
```

- The program expects **6 command-line arguments**:
  - `map rows`, `map columns`, `player row`, `player column`, `goal row`, and `goal column`.  
  - Including the executable name, `argc` should equal 7.  
- If not, an error message is printed, and `return_val` is updated to `0`.

---

#### Step 2: Parsing and Validating Individual Arguments

Each argument is processed in the following steps:  

1. Parse the argument using `strtol`:  
   ```c
   tmp_val = strtol(argv[i], &endptr, 10);
   ```
   - Converts the string argument to an integer (`base 10`).  
   - `endptr` points to any invalid character in the input.  

2. Check for invalid characters:  
   ```c
   if (*endptr != '\0') /* Check for invalid characters */
   {
       printf("Error: Invalid argument for map rows, %s\n", endptr);
       return_val = 0;
   }
   ```

3. Validate the value (e.g., non-negative, within a valid range):  
   ```c
   if (tmp_val < 5) /* Example for map rows/columns */
   {
       printf("Error: Map rows cannot be less than 5!\n");
       return_val = 0;
   }
   ```

4. Cast the validated value to `unsigned short` and update the corresponding shared variable:  
   ```c
   map_size[0] = (unsigned short)tmp_val;
   ```

The process is repeated for:  
- **`map rows` (argv[1])**  
- **`map columns` (argv[2])**  
- **`player row` (argv[3])**  
- **`player column` (argv[4])**  
- **`goal row` (argv[5])**  
- **`goal column` (argv[6])**  

---

#### Step 3: Additional Validations

If all arguments are parsed successfully (`return_val` is still 1), further checks are performed:  

```c
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
```

1. **Bounds Check**  
   - Ensures that player and goal positions are within the map dimensions.  
   - Prints errors if out of bounds.  

2. **Player and Goal Overlap**  
   - Uses `memcmp` to compare `player_pos` and `goal_pos` arrays.  
   - If the positions are identical, an error message is displayed.  

---

#### Final Step: Return the Result

```c
return return_val;
```

- Returns `1` if all validations pass.  
- Returns `0` if any error is encountered.  

---

#### Key Design Choices

1. **`strtol` over `atoi`**:  
   - Provides better error handling by detecting invalid characters in input via `endptr`.  

2. **Signed Temporary Variable (`tmp_val`)**:  
   - Enables detection of negative input values before casting to `unsigned short`.  

3. **Error Handling Strategy**:  
   - Errors are handled for each argument individually.  
   - This approach ensures all errors are reported instead of stopping at the first error.  

4. **`memcmp` for Array Comparison**:  
   - Simplifies checking if two arrays (e.g., `player_pos` and `goal_pos`) have identical values.  

---

### vi. GRID.c

Here's a refined version of your paragraph:


Before we return to the main loop in `main.c`, let's first delve into `grid.c` and explain the functions defined there. These functions, which are declared in `grid.h`, handle grid-related and game-related functionalities essential to the game's logic. Below are the function declarations outlined in `grid.h`:

```c
char **initGrid(unsigned short map_size[2], unsigned short player_pos[2], unsigned short goal_pos[2]);
void printGrid(char **grid, unsigned short map_size[2]);
void movePlayer(char user_input, char **grid, unsigned short map_size[2], unsigned short player_pos[2]);
void freeGrid(char **grid, unsigned short map_size[2]);
unsigned char winOrLose(char **grid, unsigned short map_size[2], unsigned short player_pos[2], unsigned short goal_pos[2;
```

To provide a brief overview:

- **`initGrid`** initializes the grid by taking the already initialized `map_size`, `player_pos`, and `goal_pos`.  
- **`movePlayer`** updates the player's position based on the user's input and visually reflects this change on the grid.  
- **`freeGrid`** clears the memory allocated for the grid during initialization to manage resources efficiently.  
- **`winOrLose`** checks if the player has won or lost by determining if they have reached the goal, marking the game's completion.

Let's dive into the definitions of each function and gain a deeper understanding of their implementation and purpose within the game.

---

#### initGrid

Let's dive into the `initGrid` function, breaking down each part of the code for a clearer understanding.

**Memory Allocation for the Grid**

```c
unsigned short row;
char **grid = (char **)malloc(sizeof(char *) * map_size[0]);
```

- Here, we first declare a `row` variable which will be used later in loops. The more critical part is the allocation of memory for `grid`. We allocate memory for an array of `char *` (pointers to `char`), with the number of rows determined by `map_size[0]`. This allocation is done using `malloc`, which requests memory from the heap (as opposed to the stack, where local variables are stored). 

- The reason for using `malloc` is to allow for dynamic memory allocation at runtime, ensuring the grid can be sized based on user input. We cast the result of `malloc` to `(char **)` as a good C programming practice since `malloc` returns a `void *`, which needs to be cast to the desired pointer type.

**Error Handling for Memory Allocation**

```c
if (grid != NULL) 
{
    /* proceed with grid initialization */
}
else
{
    printf("Error: Failure in allocating memory for grid!\n");
}
```

Once memory is allocated, we check if the `grid` pointer is still not `NULL`. This check is necessary because `malloc` does not raise an error if memory allocation fails; it simply returns `NULL`. If the memory allocation fails, we print an error message. This ensures that the program doesn't proceed with invalid memory references.

**Memory Allocation for Rows and Columns**

```c
for (row = 0; row < map_size[0]; row++)
{
    grid[row] = (char *)malloc(sizeof(char) * map_size[1]);

    if (grid[row] != NULL)
    {
        memset(grid[row], ' ', map_size[1]);
        /* Place player and goal */
    }
    else
    {
        map_size[0] = row;
        freeGrid(grid, map_size);
        grid = NULL;
        printf("Error: Failure in allocating memory for grid row! row=%u\n", row);
        row = map_size[0] - 1;
    }
}
```

- After successfully allocating memory for the grid itself, we need to allocate memory for each row individually. Each row is essentially a `char *`, so we allocate memory for the columns in each row (using `map_size[1]` to determine the number of columns). We check again if the memory allocation for each row succeeds. If not, we clean up any previously allocated memory using `freeGrid`, set `grid` to `NULL`, and print an error message.

- The reason we handle this row-by-row allocation is that the grid is a `char **`, meaning it's a pointer to an array of pointers. Each row is essentially a separate array, so we need to allocate memory for each of these rows individually.

**Row Initialization and Placement of Player/Goal**

```c
memset(grid[row], ' ', map_size[1]);
if (row == player_pos[0])
{
    grid[player_pos[0]][player_pos[1]] = 'P';
}
if (row == goal_pos[0])
{
    grid[goal_pos[0]][goal_pos[1]] = 'G';
}
```

Once memory is successfully allocated for a row, we initialize it using `memset`, which fills the entire row with spaces (`' '`) to represent empty spaces on the grid. Then, we check if the current row matches the player's row (`player_pos[0]`) or the goal's row (`goal_pos[0]`). If so, we place the player (`'P'`) or the goal (`'G'`) at the respective positions by updating the values in the grid.

**Handling Memory Allocation Failure**

If the memory allocation for any row fails, we do the following:

```c
map_size[0] = row;
freeGrid(grid, map_size);
grid = NULL;
printf("Error: Failure in allocating memory for grid row! row=%u\n", row);
row = map_size[0] - 1;
```

In the case where a row's memory allocation fails, we set `map_size[0]` to the current row index and call `freeGrid` to free any memory that was allocated up to that point. We also set `grid` to `NULL` to avoid potential issues with invalid pointers. To stop the loop from continuing after a failure, we adjust the `row` variable to `map_size[0] - 1`, effectively breaking out of the loop.

**Returning the Grid**

Finally, if everything succeeds, we return the allocated and populated grid:

```c
return grid;
```

The `grid` now holds the dynamic memory for all rows and columns, with the player and goal placed at the correct positions. This grid will be used throughout the game to represent the map and interact with the player.


**Key Points**

- ***Memory Allocation**: `malloc` is used to dynamically allocate memory for the grid, allowing for flexibility based on user input.*
- ***Error Handling**: We handle memory allocation errors by checking if `malloc` returns `NULL`, ensuring that the program does not proceed with invalid memory.*
- ***Row-by-Row Allocation**: Memory for each row is allocated separately because the grid is a pointer to an array of pointers.*
- ***Initialization**: After allocation, the rows are initialized with spaces (`' '`) to represent empty cells, and the player and goal positions are set accordingly.*

---

#### printGrid

In the `printGrid` function, we utilize the already initialized grid and the `map_size` data to display the current state of the game. Here's a breakdown of how the function works:


**Variable Declarations**

```c
unsigned short i;
char *h_border = malloc(sizeof(char) * (map_size[1] + 2));
```

- **`i`**: This variable is used as a loop counter later in the function.
- **`h_border`**: This dynamically allocated string is used to represent the horizontal border of the grid. The size of the border is based on the number of columns (`map_size[1]`) plus two additional characters for the edges (`*` at the beginning and end).

Dynamic allocation is used for `h_border` because the grid size is not known at compile time, and this approach ensures the border can adapt to any grid size.


**Setting the Border Value**

To initialize `h_border`:

```c
memset(h_border, '*', map_size[1] + 2);
h_border[map_size[1] + 2 - 1] = '\0';
```

- `memset` is used to fill the `h_border` string with the `'*'` character, creating a visual boundary for the grid.
- The last character is set to `'\0'` to properly terminate the string.

**Printing the Grid**

```c
system("clear");

printf("%s\n", h_border);
for (i = 0; i < map_size[0]; i++)
{
    printf("*%s*\n", grid[i]);
}
printf("%s\n", h_border);
```

- **`system("clear")`**: This makes a system call to clear the console screen, ensuring the grid is displayed cleanly. On Unix-based systems, the `"clear"` command works to refresh the screen.
- **`printf("%s\n", h_border)`**: Prints the top border of the grid using the `h_border` string.
- **`for` loop**: Iterates through each row of the grid (`grid[i]`) and prints it. The format string `"*%s*"` adds `'*'` to the beginning and end of each row, creating the appearance of vertical borders.
- **Bottom border**: The final `printf` prints the bottom border using the same `h_border` string.

**Key Points**

- ***Dynamic Border Creation**: By dynamically allocating `h_border` and setting its value using `memset`, we ensure that the border size matches the grid's width (`map_size[1]`), making the function adaptable to different map sizes.*
- ***String Formatting**: Each row of the grid is treated as a string (a null-terminated `char` array), which simplifies printing the grid contents row by row.*
- ***System Command**: The `system("clear")` call is used for aesthetic purposes to refresh the terminal screen before printing the updated grid. This ensures that every grid update looks clean without cluttering the terminal.*

---

#### breakFloor

The `breakFloor` function is not directly called in `main.c` but is utilized within `movePlayer`. Its primary purpose is to randomly "break" a floor tile by marking it with an `'X'`. Here's the function definition with an explanation:

**Function Definition**

```c
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
```


**Purpose**:
- The function randomly selects a position in the grid and marks it with an `'X'`, representing a broken floor tile.
- The position must be an empty space (`' '`) to avoid overwriting other elements like the player (`'P'`) or the goal (`'G'`).

**Random Position Generation**:
- `random(0, map_size[0] - 1)` generates a random row index.
- `random(0, map_size[1] - 1)` generates a random column index.
- These values are stored in the `x_pos` array, representing the randomly chosen position in the grid.

**Ensuring a Valid Position**:
- The `while (!unique)` loop continues until a valid, unique empty position is found.
- Inside the loop, if the randomly selected position corresponds to an empty space (`' '`), the position is marked as `'X'`, and the `unique` flag is set to `1` to exit the loop.

**Using a Random Number Generator**:
- The `random` function (assumed to be from an external library) is used to generate random integers within the specified range. This ensures that the position is within the grid's bounds.

---

#### _borderless

The `_borderless` function is used within the `movePlayer` function when the `BORDERLESS` condition is enabled. This function ensures that if the player attempts to move beyond the grid's boundaries, their position "wraps around" to the opposite side, creating a seamless transition across rows or columns.

**Function Definition**

```c
void _borderless(int pos[2], unsigned short map_size[2])
{
    if (pos[0] < 0)
    {
        pos[0] = map_size[0] - 1; // Wrap around to the bottom row
    }
    else if (pos[0] >= map_size[0])
    {
        pos[0] = 0; // Wrap around to the top row
    }

    if (pos[1] < 0)
    {
        pos[1] = map_size[1] - 1; // Wrap around to the rightmost column
    }
    else if (pos[1] >= map_size[1])
    {
        pos[1] = 0; // Wrap around to the leftmost column
    }
}
```

**Explanation of Behavior**

- **Inputs**:
   - `pos[2]`: The player's current position represented as a 2D coordinate `[row, column]`.
   - `map_size[2]`: The grid's dimensions `[number of rows, number of columns]`.

- **Purpose**:
   - This function adjusts the player's position if they attempt to move out of bounds, wrapping them around to the other side of the grid.
   - The function accounts for both row (`pos[0]`) and column (`pos[1]`) movements.

- **How It Works**:
   - For the **row index** (`pos[0]`):
     - If `pos[0]` is less than `0` (above the top row), it is wrapped to the bottom row (`map_size[0] - 1`).
     - If `pos[0]` exceeds the last row (`map_size[0]`), it is wrapped to the top row (`0`).
   - For the **column index** (`pos[1]`):
     - If `pos[1]` is less than `0` (left of the first column), it is wrapped to the rightmost column (`map_size[1] - 1`).
     - If `pos[1]` exceeds the last column (`map_size[1]`), it is wrapped to the first column (`0`).

- **Effect**:
   - The result is a "borderless" behavior where the grid loops in both directions:
     - Moving out of the top boundary places the player at the bottom.
     - Moving out of the bottom boundary places the player at the top.
     - Moving out of the left boundary places the player at the rightmost side.
     - Moving out of the right boundary places the player at the leftmost side.

**Example**

For a grid of size `5x5` (`map_size[0] = 5`, `map_size[1] = 5`):

| Initial Position (`pos`) | Movement       | Adjusted Position (`pos`) |
|--------------------------|----------------|---------------------------|
| `[0, 2]`                | Up (row -1)    | `[4, 2]` (bottom wrap)    |
| `[4, 2]`                | Down (row +1)  | `[0, 2]` (top wrap)       |
| `[2, 0]`                | Left (col -1)  | `[2, 4]` (right wrap)     |
| `[2, 4]`                | Right (col +1) | `[2, 0]` (left wrap)      |

---

#### movePlayer

The `movePlayer` function is responsible for managing the player's movement based on user input, updating their position on the grid, and ensuring that movement adheres to specific game rules. Below is a detailed breakdown of the function.


**Variable Declarations**

```c
int future_pos[2];

future_pos[0] = (int)player_pos[0];
future_pos[1] = (int)player_pos[1];
```

- **Purpose of `future_pos`:**
   - This variable temporarily holds the player's potential next position on the grid, based on their current position (`player_pos`) and input direction.
   - Declared as `int` to handle edge cases where calculations might result in negative values, especially for borderless movement.

- **Why `int` instead of `unsigned short`?**
   - Using `unsigned short` for `future_pos` could cause issues when subtracting values at the grid's edges:
     - For example, if `player_pos[0]` is `0` and the player attempts to move up (`future_pos[0]--`), the result would underflow to `65535` (maximum value for `uint16_t`), causing a bug.
   - With `int`, negative values can be represented, which is particularly useful for handling conditions like wrapping in borderless mode.

**Switch Case for Input Handling**

```c
switch (user_input)
{
case 'w':
    future_pos[0]--; // Move up
    break;

case 's':
    future_pos[0]++; // Move down
    break;

case 'a':
    future_pos[1]--; // Move left
    break;

case 'd':
    future_pos[1]++; // Move right
    break;

default:
    break;
}
```

- **Switch-Case over If-Else:**
   - Switch statements are more efficient for multiple discrete cases compared to `if-else` chains.
   - Each case corresponds to a valid movement:
     - `'w'`: Decrease the row index to move up.
     - `'s'`: Increase the row index to move down.
     - `'a'`: Decrease the column index to move left.
     - `'d'`: Increase the column index to move right.

- **Result:**
   - The `future_pos` array is updated to reflect the intended movement direction.

**Macro Conditional for Borderless Mode**

```c
#ifdef BORDERLESS
    _borderless(future_pos, map_size);
#endif
```

- **Explanation:**
   - The `#ifdef BORDERLESS` directive ensures that the `_borderless` function is called only if `BORDERLESS` mode is enabled during compilation.
   - `_borderless` adjusts the `future_pos` so that if the player moves out of bounds, they "wrap around" to the other side of the grid.
     - For example:
       - Moving up from the top row wraps the player to the bottom row.
       - Moving right from the last column wraps the player to the first column.

- **Purpose:**
   - This condition makes the game grid borderless and adds a dynamic gameplay element.

---

**Validating and Moving the Player**

```c
if (!(future_pos[0] == (int)player_pos[0] && future_pos[1] == (int)player_pos[1]) &&
    future_pos[0] >= 0 && future_pos[0] < map_size[0] &&
    future_pos[1] >= 0 && future_pos[1] < map_size[1] &&
    grid[future_pos[0]][future_pos[1]] != 'X')
{
    grid[player_pos[0]][player_pos[1]] = ' '; /* Clear the player's current position */
    player_pos[0] = (unsigned short)future_pos[0]; /* Update player row position */
    player_pos[1] = (unsigned short)future_pos[1]; /* Update player column position */
    grid[player_pos[0]][player_pos[1]] = 'P'; /* Place the player in the new position */

    breakFloor(grid, map_size); /* Introduce a new broken floor tile */
}
```

- **Condition Breakdown:**
   - Ensures that:
     1. The player is attempting to move (i.e., `future_pos` is not equal to `player_pos`).
     2. The `future_pos` is within the grid's valid range (`>= 0` and `< map_size`).
     3. The target cell (`grid[future_pos[0]][future_pos[1]]`) is not a broken floor (`'X'`).

- **Actions If Valid:**
   - **Clear the current position:** 
     - The cell where the player was located is reset to `' '` (empty space).
   - **Update player position:**
     - `player_pos` is updated to `future_pos` for both row and column indices.
   - **Place the player in the new position:**
     - The cell at `future_pos` is updated to `'P'` to represent the player's presence.
   - **Break a new floor tile:**
     - `breakFloor` is called to randomly select an empty space on the grid and mark it as a broken floor (`'X'`).

Once validated, the function updates the grid to reflect the player's new position and introduces a broken floor tile for added gameplay complexity.

---

#### freeGrid

The `freeGrid` function is responsible for properly deallocating memory that was dynamically allocated for the grid, thereby preventing memory leaks. Below is a detailed breakdown of how this function works and why it is structured this way.


**Function Definition**

```c
void freeGrid(char **grid, unsigned short map_size[2])
{
    unsigned short i;

    if (grid != NULL)
    {
        for (i = 0; i < map_size[0]; i++)
        {
            free(grid[i]); // Free each row of the grid
        }

        free(grid); // Free the entire grid array
        grid = NULL; // Set grid pointer to NULL
    }
}
```

**Explanation**

- **Parameter Details:**
   - `char **grid`: This is a pointer to an array of pointers representing the 2D grid.
   - `unsigned short map_size[2]`: An array representing the grid dimensions `[rows, columns]`.

- **Purpose:**
   - The function deallocates memory row-by-row, followed by deallocating the entire grid pointer itself.
   - Ensures proper memory management by freeing each row individually before freeing the main pointer.

- **How It Works:**
   - **Check if `grid` is not NULL:** 
     - This prevents trying to free memory that hasn't been allocated or has already been freed, which could lead to undefined behavior or a program crash.
   - **Iterate through each row:**
     - The loop runs from `0` to `map_size[0] - 1`, representing the number of rows.
     - Each row (`grid[i]`) is freed individually. This is crucial because the grid is an array of pointers, and each pointer points to a dynamically allocated array.
   - **Free the entire grid pointer:**
     - After all rows are freed, the `grid` pointer itself is deallocated to release the memory used by the array of pointers.
   - **Set `grid` to NULL:**
     - Setting `grid` to `NULL` after freeing it helps prevent dangling pointers, making the code safer and less error-prone.


**Why Free Each Row Separately?**
- The `grid` is a 2D array allocated using a series of `malloc` calls:
  - First, memory is allocated for an array of pointers representing the rows.
  - Then, each row itself is allocated separately.
- This requires each row to be freed individually because `free` only releases memory that was allocated in a single `malloc` call. Freeing just `grid` without freeing the rows would lead to memory leaks.


**Error Handling and Best Practices**
- **`if (grid != NULL)`:** 
  - This is an important check because attempting to free a `NULL` pointer has no effect, but it’s a good practice to ensure the pointer is valid.
- **Set `grid` to `NULL`:**
  - This is to prevent accidental access to freed memory, which could lead to undefined behavior.

---

#### winOrLose featuring `_isValid` and `_dfs`

The `winOrLose` function determines the outcome of the game by checking whether the player erached the goal or can reach the goal position (`G`) on the grid. It uses two helper functions: `_isValid` and `_dfs`. Here's a breakdown of each function and how they collectively work to decide the game's state:

---

##### `_isValid`: Validate a Grid Position

**Definition:**
```c
unsigned char _isValid(int pos[2], unsigned char **visited, char **grid, unsigned short map_size[2])
{
    return pos[0] >= 0 && pos[0] < map_size[0] &&
           pos[1] >= 0 && pos[1] < map_size[1] &&
           grid[pos[0]][pos[1]] != 'X' && 
           !visited[pos[0]][pos[1]];
}
```

**Explanation:**
- **Purpose:** Checks if a given position on the grid is:
  1. Within the grid boundaries.
  2. Not a blocked cell (`X`).
  3. Not already visited during the search.
- **Parameters:**
  - `pos[2]`: The position being validated.
  - `visited`: A 2D array marking visited cells.
  - `grid`: The grid containing the player's current state.
  - `map_size`: The size of the grid.
- **Returns:** 
  - `1` (true) if the position is valid.
  - `0` (false) otherwise.

---

##### `_dfs`: Depth-First Search

**Definition:**
```c
unsigned char _dfs(int pos[2], unsigned char **visited, char **grid, unsigned short map_size[2])
```

**Explanation:**
- **Purpose:** Implements a recursive **Depth-First Search (DFS)** algorithm to explore paths from the player's position to the goal.
- **Parameters:**
  - `pos[2]`: The current position during the DFS.
  - `visited`: A 2D array marking visited cells.
  - `grid`: The grid containing the player's current state.
  - `map_size`: The size of the grid.
- **Steps:**
  1. **Borderless Mode (Optional):** 
     - If `BORDERLESS` is defined, calls `_borderless` to handle out-of-bound positions by wrapping them around.
  2. **Validate Position:** 
     - Calls `_isValid` to ensure the current position is within bounds, not blocked, and unvisited.
  3. **Goal Check:**
     - If the current position is the goal (`G`), the search ends successfully.
  4. **Recursive Exploration:**
     - Marks the current cell as visited and recursively explores all four directions:
       - **Up:** `(pos[0] - 1, pos[1])`
       - **Down:** `(pos[0] + 1, pos[1])`
       - **Left:** `(pos[0], pos[1] - 1)`
       - **Right:** `(pos[0], pos[1] + 1)`
     - The recursion stops as soon as a path to the goal is found.
  5. **Return:** 
     - Returns `1` (true) if a path to the goal is found, otherwise `0`.

---

##### `winOrLose`: Determine Game State

**Definition:**
```c
unsigned char winOrLose(char **grid, unsigned short map_size[2], unsigned short player_pos[2], unsigned short goal_pos[2])
```

**Explanation:**
- **Purpose:** Determines if the player reached the goal or can reach the goal or not by using the DFS algorithm.
- **Parameters:**
  - `grid`: The grid containing the current game state.
  - `map_size`: The size of the grid.
  - `player_pos`: The player's current position.
  - `goal_pos`: The goal's position.
- **Steps:**
  1. **Allocate `visited` Array:**
     - Dynamically allocates a 2D `visited` array to track cells visited during the DFS. Each cell is initialized to `0` using `memset`.
  2. **Immediate Win Check:**
     - Compares `player_pos` and `goal_pos`. If they are the same, prints "You Win!" and returns `1`.
  3. **Call `_dfs`:**
     - Initiates a DFS from the player's current position to search for a path to the goal.
     - If `_dfs` returns `0` (no path found), prints "You Lose!" and sets the return value to `1`.
  4. **Free Memory:**
     - Frees the dynamically allocated `visited` array to prevent memory leaks.
  5. **Return:** 
     - Returns `1` if the game state has been determined (win or lose), otherwise `0`.

---

##### How They Work Together

1. **`winOrLose`:**
   - Called from the main game loop to determine if the game has reached an end state.
   - Prepares the necessary data (like `visited` array) and checks for an immediate win condition.

2. **`_dfs`:**
   - Executes the actual pathfinding to check if the goal is reachable from the player's current position.
   - Handles recursion, marking visited cells, and navigating the grid.

3. **`_isValid`:**
   - Ensures that each position visited during DFS is valid (within bounds, not blocked, and unvisited).

Together, these functions enable the program to decide whether the player has won, lost, or can continue the game.

### vii. Towards the main game loop

The main gameplay logic revolves around initializing the game environment, entering the main gameplay loop, and properly cleaning up resources after the game ends. Here's a detailed breakdown:

---

#### Initialization

```c
/* Initialize grid and random number generator */
grid = initGrid(map_size, player_pos, goal_pos);
initRandom();
```

- **`initGrid`:** 
  - This function initializes the game grid and sets up the player (`P`) and goal (`G`) positions based on the given parameters (`map_size`, `player_pos`, `goal_pos`).
  - If memory allocation fails at any point during the grid creation, `initGrid` will return `NULL`, and an error message will already have been printed by the function.

- **`initRandom`:** 
  - This function initializes the random number generator, which is used for functions like `breakFloor` to determine random positions for obstacles. It is part of the library provided in the assessment.

- The conditional check (`if (grid != NULL)`) ensures that the rest of the game logic proceeds only if the grid is successfully initialized.

---

#### Pre-Loop Grid Display

```c
/* Display the current grid */
printGrid(grid, map_size);
```

- Before entering the main gameplay loop, the grid is displayed to the user using the `printGrid` function.
- This initial print ensures that the player sees the starting state of the grid before any input is processed. It avoids redundancy by simplifying the logic within the loop, as the grid is printed only after an action is taken.

---

#### Main Gameplay Loop

```c
while (!winOrLose(grid, map_size, player_pos, goal_pos))
{
    /* Move player and check game status */
    movePlayer(getUserInput(), grid, map_size, player_pos);

    /* Display the current grid */
    printGrid(grid, map_size);
}
```

- **While Loop Condition:**
  - The loop continues as long as `winOrLose` returns `0`, indicating the game is still ongoing.
  - `winOrLose` determines the game's end state (win or lose) by checking if the player can reach the goal. If the function returns `1`, the loop stops.

- **Inside the Loop:**
  1. **Player Movement:**
     - `movePlayer` handles the player's movement based on input retrieved from the `getUserInput` function.
     - The `getUserInput` function is defined in `utils.c` (to be explained later) and captures user input without requiring the user to press "Enter".
     - `movePlayer` ensures the movement is valid and updates the grid accordingly.

  2. **Updated Grid Display:**
     - After each movement, the updated grid is displayed to reflect the player's new position and any changes (e.g., broken floors marked as `X`).

---

#### Memory Cleanup

```c
/* Free grid memory after gameplay */
freeGrid(grid, map_size);
```

- After the game ends (either a win or loss), `freeGrid` is called to deallocate all the memory allocated for the grid.
- This includes freeing each row and then freeing the grid itself. Setting `grid` to `NULL` ensures there are no dangling pointers.

---

#### Why is the Code Organized This Way?

1. **Grid Initialization:**
   - Placing grid initialization and random number setup at the start ensures the game is ready before any actions are taken.
   - The check for `grid != NULL` prevents the program from proceeding in case of allocation failures.

2. **Pre-Loop Grid Display:**
   - Displaying the grid before the loop avoids redundant logic within the loop and provides a clear initial state to the player.

3. **Minimalism in the Loop:**
   - By organizing the loop to handle only movement and grid display, the code remains clean and concise.
   - All win/lose checks are encapsulated in `winOrLose`, simplifying the condition handling.

4. **Memory Management:**
   - Explicitly freeing the grid after the game ensures no memory leaks, maintaining good programming practices.

---

### viii. getUserInput

The `getUserInput` function is responsible for capturing the player's movement input in real-time without requiring the user to press "Enter" after entering their choice. Here's a step-by-step breakdown:

---

#### Function Definition
```c
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
```

---

#### Step-by-Step Breakdown

1. **Prompting the Controls**
   ```c
   printf("Press w to go up\nPress s to go down\nPress a to go left\nPress d to go right\n");
   ```
   - The function prints out the movement controls, allowing the player to understand which keys (`w`, `a`, `s`, `d`) correspond to each direction (up, left, down, right).
   - This message is displayed after the grid is printed, providing the user with clear and immediate feedback.

2. **Temporary Disabling of Input Buffering**
   ```c
   disableBuffer();
   ```
   - The `disableBuffer` function (provided by the `terminal.h` library in the assessment) disables input buffering in the terminal.
   - Normally, terminals buffer the user's input until "Enter" is pressed. Disabling buffering allows the program to immediately capture a single character without requiring the user to press "Enter."

3. **Capturing Input**
   ```c
   scanf(" %c", &input);
   ```
   - `scanf` is used to read a single character input from the user, storing it in the `input` variable.
   - The `" %c"` format ensures that leading whitespace characters (if any) are ignored.

4. **Re-enabling Input Buffering**
   ```c
   enableBuffer();
   ```
   - After capturing the input, `enableBuffer` re-enables the terminal's input buffering.
   - This ensures normal terminal behavior is restored for subsequent operations.

5. **Returning the Input**
   ```c
   return input;
   ```
   - The function returns the captured character (`input`) to the calling function, which in this case is the `movePlayer` function in the main gameplay loop.

---

#### Purpose of the Function

- **Real-Time Input Capture:**
  - The function's primary goal is to capture user input in real-time, making the gameplay more dynamic and interactive.
  - Players can provide directional input (`w`, `a`, `s`, `d`) without pressing "Enter," creating a smoother user experience.

- **Buffer Management:**
  - By temporarily disabling and re-enabling the terminal buffer, the function ensures input handling is efficient and does not interfere with the terminal's normal behavior outside the game.

---

### ix. RETURN 0

In C, the `return 0;` statement in a function, typically in the `main` function, serves a specific purpose related to the program's execution status. Let me break it down:

<img src="https://media1.tenor.com/m/nep7WtDOM70AAAAC/benson-regular-show.gif" alt="Let me break it down" />

---

#### Role of the `main` Function
The `main` function in C is the entry point of a program. When the program is executed, the operating system starts its execution by calling the `main` function.

- The `main` function is expected to return an integer, as defined by its signature:
  ```c
  int main() { ... }
  ```
- This return value communicates the program's status back to the operating system.

---

#### Meaning of `return 0;`
The value returned by the `main` function serves as an **exit status** for the program:

- **`0`**:
  - Conventionally indicates **successful execution** of the program.
  - It tells the operating system that the program ran as expected without errors.
  ```c
  return 0;
  ```
- **Non-Zero Values**:
  - Usually indicate an **error or abnormal termination**.
  - Programmers use specific non-zero values to signal different types of errors. For example:
    ```c
    return 1; /* General error */
    return 2; /* Specific error */
    ```

---

#### Why Is `return 0;` Important?
- **Communication with the Operating System:**
  - The exit status (`0` or non-zero) allows the operating system or calling processes (like scripts) to determine whether the program executed successfully.
  - Example in a Unix shell:
    ```bash
    ./my_program
    if [ $? -eq 0 ]; then
        echo "Program ran successfully"
    else
        echo "Program encountered an error"
    fi
    ```
  - `$?` contains the exit status of the last command.

- **Standard Practice:**
  - It is a good habit to explicitly return `0` in `main` to indicate that the program completed without issues.

---

#### What If You Don’t Use `return` in `main`?
- In modern C standards (`C99` and later), if you omit the `return` statement, the compiler implicitly adds `return 0;` at the end of the `main` function.
  ```c
  int main() {
      printf("Hello, World!\n");
      /* No return statement */
  }
  ```
  This is equivalent to:
  ```c
  int main() {
      printf("Hello, World!\n");
      return 0; /* Implicitly added by the compiler */
  }
  ```

- However, it is still recommended to explicitly write `return 0;` for clarity and maintainability, especially in older C standards (`C89`/`C90`) where omitting it might result in undefined behavior.

---

## 5. <img src="/images/mrd.png" alt="Make it. Run It. Done." style=""/>



To execute C code, we must first compile it. This is because C is a high-level language that needs to be translated into machine code for execution. This compilation process involves several steps:

1. **Preprocessing**:  
   The preprocessor handles directives like `#include` and `#define`. It prepares the source code by inserting header files and replacing macros.

2. **Compilation**:  
   The compiler converts the preprocessed code into assembly language.

3. **Assembly**:  
   The assembler translates the assembly code into object files (`.o`). These files contain machine code but are not yet complete for execution.

4. **Linking**:  
   The linker combines all object files, resolves references, and creates an executable file.

For this project, we’ll use the **GNU Compiler Collection (GCC)**, which handles all these steps, including linking.

---

### Compiling with GCC
We use GCC to compile our code. Since we have multiple `.c` files (some provided as external libraries and others written by us), we need to:

1. **Compile each `.c` file into `.o` object files**:  
   This is done using the `-c` flag with GCC. For example:  
   ```bash
   gcc -c -Wall -Werror -ansi -pedantic src/main.c -o build/main.o
   ```
   - **`-Wall`**: Enables all warning messages.  
   - **`-Werror`**: Treats all warnings as errors.  
   - **`-ansi`**: Enforces ANSI C compliance (C89 standard).  
   - **`-pedantic`**: Ensures strict adherence to the C standard.  

   These flags ensure our code meets the assignment requirements.  
   
2. **Link all `.o` files into a final executable**:  
   After generating all `.o` files, we link them into a single executable (e.g., `escape`).

---

### Using `make` and `Makefile`
Compiling and linking files manually can be tedious. To streamline the process, we use `make` with a `Makefile`. This automates building the executable by defining rules and dependencies.

Before diving into the Makefile, it’s essential to understand **`.d` files**:
- **Dependency Files (`.d`)**:  
   These files help `make` track which source files have changed and only recompile those. They are created using GCC with the `-MMD` flag and ensure efficient builds.

---

### Makefile Explanation

Here’s the Makefile for our project:

```makefile
# Compiler and flags
CC = gcc
COMMON_CFLAGS = -Wall -Werror -ansi -pedantic
CFLAGS = $(COMMON_CFLAGS)
LDFLAGS = 

# Conditional compilation for BORDERLESS
ifeq ($(BORDERLESS), 1)
	CFLAGS += -DBORDERLESS
endif
```
- **`CC`**: Specifies the compiler (GCC in this case).  
- **`CFLAGS`**: Flags for compilation. `-DBORDERLESS` is added if `BORDERLESS` is set to `1`.  

```makefile
# Directories
SRCDIR = src
INCDIR = include
LIBDIR = lib
BINDIR = bin
OBJDIR = build
TESTDIR = tests
```
Defines directory paths for source files, includes, libraries, binaries, and object files.

```makefile
# File extensions and patterns
SRC = $(wildcard $(SRCDIR)/*.c)
LIB_SRC = $(wildcard $(LIBDIR)/*.c)
TEST_SRC = $(wildcard $(TESTDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
LIB_OBJ = $(LIB_SRC:$(LIBDIR)/%.c=$(OBJDIR)/%.o)
TEST_OBJ = $(TEST_SRC:$(TESTDIR)/%.c=$(OBJDIR)/%.o)

# Dependency files
DEP = $(OBJ:.o=.d) $(LIB_OBJ:.o=.d) $(TEST_OBJ:.o=.d)
```
- **`$(wildcard)`**: Lists all `.c` files in the specified directory.  
- **`OBJ`**: Maps source files to their corresponding object files.  
- **`DEP`**: Maps object files to their dependency files.

```makefile
# Executable name
EXE = $(BINDIR)/escape

# Build target
all: $(EXE)
```
- **`all`**: The default target to build the executable `escape`.

```makefile
# Link the final binary
$(EXE): $(OBJ) $(LIB_OBJ) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIB_OBJ) $(LDFLAGS)
```
Links object files into the final executable.

```makefile
# Compile source files into the obj directory
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBDIR) -MMD -MF $(@:.o=.d) -c $< -o $@
```
Compiles `.c` files to `.o` files.  
- **`-I`**: Specifies include directories.  
- **`-MMD -MF`**: Generates `.d` files for dependencies.  

```makefile
# Ensure directories exist
$(BINDIR) $(OBJDIR):
	mkdir -p $@
```
Creates required directories if they don’t exist.

```makefile
# Clean target
clean:
	rm -rf $(OBJDIR) $(BINDIR) $(DEP)
```
Removes generated files and directories to reset the project state.

```makefile
# Include dependency files
-include $(DEP)

# Phony targets
.PHONY: all clean test
```
- **`-include $(DEP)`**: Includes dependency files if they exist.  
- **`.PHONY`**: Marks non-file targets like `all` and `clean` to avoid conflicts.

---

### Building and Running
To build and run the program:
1. **Build**:  
   - Run `make` or `make all` to compile and link the program into `bin/escape`.
   - To build with borderless mode use `make BORDERLESS=1`

2. **Clean**:  
   Run `make clean` to remove all generated files.

3. **Run**:  
   Use the following command to execute the program:  
   ```bash
   ./bin/escape <row_map> <col_map> <row_player> <col_player> <row_goal> <col_goal>
   ```

   Here, the parameters specify the map size and initial positions.

--- 

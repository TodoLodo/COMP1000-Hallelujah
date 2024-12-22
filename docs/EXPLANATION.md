# Mighty Explanation

## Table of Contents
1. [Project Directory Structure](#project-directory-structure)
2. [Approach and Logic](#approach-and-logic)
3. [Pre-thinking and Design Decisions](#pre-thinking-and-design-decisions)
4. [Step-by-Step Logical Flow](#step-by-step-logical-flow)

---

## Project Directory Structure

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

1. **bin**
    - Stores the compiled executables or binaries after the build process.
    - Keeps the main project directory clean by separating build artifacts from source code.

2. **build**
    - Temporary build files generated during the compilation process, such as object files (`.o`) and dependency files.
    - Helps maintain a clear distinction between source code and intermediary compilation outputs.

3. **docs**
    - Includes all project documentation files, such as:
        - `EXPLANATION.md`: A deep dive into the project's design and logic.
        - `SPECIFICATION.md`: An overview of the project with instructions for setup and usage.
    - Can also store additional files like design documents or external references.

4. **images**
    - Houses visual assets like diagrams, flowcharts, or screenshots used in documentation.
    - Useful for illustrating key concepts or providing visual aids for users.

5. **include**
    - Contains all the header files (`.h`) used in the project.
    - Promotes modularity by allowing function declarations, macro definitions, and data structure declarations to be easily shared across multiple source files.

6. **lib**
    - Stores external or provided library code, including `.h` and `.c` files given as part of the assignment.
    - Keeps the project modular and organized by isolating reusable components.

7. **src**
    - The main directory for source code files (`.c`) that implement the core functionality of the project.
    - Typically contains implementation code specific to your project objectives.

8. **tests**
    - Contains test cases to verify the functionality and correctness of the code.
    - May include unit tests, integration tests, or scripts to automate the testing process.

### Why This Structure?
This structure:
- Follows a logical hierarchy that separates concerns (source, headers, tests, etc.).
- Facilitates easier navigation and understanding for contributors.
- Aligns with widely accepted standards, making it easier for others to contribute or review your work.

---

## Approach and Logic

### **Objective**

The main goal of this program is to create an interactive terminal-based game called **escape**. The key functionalities are:

1. Accept and validate command-line arguments to configure the game environment.
2. Render a 2D map dynamically, showing the player's position, the goal, and collapsing floor grids.
3. Respond to user input for player movement, ensuring boundary and obstacle constraints are adhered to.
4. Randomize floor collapses to introduce unpredictability, making the game engaging.
5. Implement winning and losing conditions, ending the game based on player actions and map state.
6. Add a **BORDERLESS** compilation option to allow advanced movement across map edges.

---

### Key Challenges and Solutions

#### 1. Command-Line Argument Parsing
- **Challenge**: Validate six numerical inputs for rows, columns, and positions for the player and goal.
- **Solution**:  
  - Use `argc` and `argv` to check for the exact number of arguments.
  - Parse inputs using `atoi()`, ensuring proper integer conversion and range checks.
  - Handle invalid input gracefully with error messages and a loop prompting for corrections, avoiding abrupt program termination via `exit()`.

#### 2. Map Interface Rendering
- **Challenge**: Dynamically display a 2D grid that updates after each player movement.
- **Solution**:  
  - Use `*` for borders, `P` for the player, `G` for the goal, and `X` for collapsed grids.
  - Clear the terminal screen with `system("clear")` (Unix) before re-rendering the updated map.
  - Implement functions to generate the map, place the player and goal, and update the map after each turn.

#### 3. User Input and Movement
- **Challenge**: Process valid movement commands while ignoring invalid ones, ensuring the player cannot move into borders or collapsed grids.
- **Solution**:  
  - Use `scanf()` to read user input.
  - Map movement commands (`w`, `a`, `s`, `d`) to directional changes in the player's coordinates.
  - Check boundaries and prevent illegal movements with conditional statements.

#### 4. Randomized Collapsing Floor
- **Challenge**: Randomly collapse a floor grid after each movement, avoiding the player and goal positions.
- **Solution**:  
  - Use a random number generator to select a non-collapsed grid position.
  - Ensure the chosen position does not overlap with the player or goal by validating against their coordinates.
  - Update the grid state with `X` for collapsed tiles.

#### 5. Win/Lose Conditions
- **Challenge**: Detect when the player has won or lost.
- **Solution**:  
  - Win Condition: Check if the player's position matches the goal's coordinates after a move.
  - Lose Condition: Determine if all paths to the goal are blocked by collapsed grids, trapping the player or goal.

#### 6. Conditional Compilation with BORDERLESS
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

## Pre-thinking and Design Decisions

### 1. Structuring Code into Multiple Files
- **Reasoning**:  
  - To maintain readability and modularity, the main function should act as the central hub, only responsible for calling other structured code. It should not be overloaded with implementation details.
  - By splitting the code into multiple files, each dedicated to a specific responsibility, it becomes easier to manage, debug, and extend. This also aligns with the assignment criterion of having more than one or two `.c` files.
- **Implementation**:  
  - **`grid.c`**: Handles player movement, grid manipulations, and rendering functionalities. All grid-related operations will be contained here for logical grouping.
  - **`utils.c`**: Manages command-line argument parsing, validation, and user input handling. Keeping utility functions separate improves clarity and avoids clutter in other files.
  - **`main.c`**: Contains the main function, the central loop, and declarations for shared variables. This file serves as the entry point for the program, providing a clear distinction of purpose.

### 2. Logical Grouping of Related Data
- **Reasoning**:  
  - Although map rows, columns, player positions, and goal positions are given as separate command-line arguments, grouping them logically into arrays provides a more structured way to handle related data.
  - Arrays in C behave as memory pointers, simplifying function calls and value updates without needing to pass multiple separate variables.
- **Implementation**:  
  - **`map_size[2]`**: Stores the number of rows and columns of the map.
  - **`player_pos[2]`** and **`goal_pos[2]`**: Hold the row and column coordinates of the player and goal respectively.

### 3. Optimizing Memory Usage with Data Types
- **Reasoning**:  
  - The assignment specifies constraints on the map size, indicating that values will not exceed a 16-bit integer. Additionally, negative values are irrelevant for these variables.
  - Using `unsigned short` (16-bit) instead of `int` (32-bit) helps reduce memory consumption while ensuring the values fall within the expected range. The unsigned modifier ensures no negative values are possible, making the code more precise and efficient.
- **Implementation**:  
  - **`unsigned short`** (equivalent to `uint16_t` in C99+): Used for `map_size`, `player_pos`, and `goal_pos` to minimize memory usage while meeting the program's requirements.

### 4. Main Loop and Termination Handling
- **Reasoning**:  
  - Since the assignment prohibits the use of `exit()` or returning from the main function to terminate the program, a boolean-like variable is used to control the main loop.
- **Implementation**:  
  - **`game_running`**: A variable initialized to `1` (true). The main loop continues running as long as this variable remains true. It is set to `0` (false) when a win or lose condition is met.

### 5. Grid Representation
- **Reasoning**:  
  - The grid is the program's central element, representing the player, goal, borders, and collapsed floors. Using a 2D array of `char` simplifies visualization and ensures each element requires only 8 bits of memory.
  - Characters (`*`, `P`, `G`, `X`, and spaces) provide a straightforward way to represent the grid visually.
- **Implementation**:  
  - **`char **grid`**: The 2D array holds the current state of the map. The size is determined by the command line arguments passed.

### 6. Naming Conventions
- **Reasoning**:  
  - File and variable names should clearly reflect their purpose. This makes the code easier to understand and navigate.
- **Implementation**:  
  - Files like `grid.c`, `utils.c`, and `main.c` are named based on their responsibilities, making it intuitive to locate functions and logic.
  - Variable names such as `map_size`, `player_pos`, and `goal_pos` are chosen for clarity and ease of understanding.

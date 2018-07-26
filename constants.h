#ifndef CONSTANTS_H
#define CONSTANTS_H

#define WIDTH 11
#define HEIGHT 18
#define LOST_ROW 3
#define NUM_ROWS_INVISIBLE 3

// Level Probabilities
#define LEVEL1 { 2, 2, 2, 2, 1, 2, 1 }
#define LEVEL2 { 1, 1, 1, 1, 1, 1, 1 }
#define LEVEL3 { 1, 1, 1, 1, 2, 1, 2 }
// Block Identifiers
#define BLOCKS { 'I', 'J', 'L', 'O', 'S', 'T', 'Z' }
// Possible Commands
#define COMMANDS {"left", "right", "down", "clockwise", "counterclockwise", "drop", "levelup", "leveldown", "restart", "hint", "random", "norandom"}
#define COMMANDS_SIZE 12

#define LEVEL_MIN 0
#define LEVEL_MAX 4

#endif

#ifndef __TICTACTOE_H
#define __TICTACTOE_H


// define constants that keeps status of winner of game
#define PLAYER_WINS 5
#define CPU_WINS 6
#define TIE 7

// define constants that signify the locations of board and who has played where
#define EMPTY 48
#define X 49
#define O 50

// define constants used to signify if CPU has found a spot to play
#define FOUND 1
#define NOT_FOUND 0

// methods that are used
void draw_grid(char grid[3][3]);
void CPU_move(char grid[3][3]);
int find_row(char grid[3][3], int check);
int find_column(char grid[3][3], int check);
int find_diagonal(char grid[3][3], int check);
int check_diagonals(char grid[3][3]);
int check_rows(char grid[3][3]);
int check_cols(char grid[3][3]);
int check_full(char grid[3][3]);
void game_over(int winner);


#endif

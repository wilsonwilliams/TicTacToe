#ifndef __TICTACTOE_CPP
#define __TICTACTOE_CPP

#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "tictactoe.hpp"

// no need to reference std::cout, std::cin, etc
using namespace std;


// method prints the grid
void draw_grid(char grid[3][3]) {
    
    // loop through each row (i = rows)
    for (int i = 0; i < 3; ++i) {

        // loop through each column (j = cols)
        for (int j = 0; j < 3; ++j) {

            // for first two columns in each row, print X, O, or nothing and then a |
            // for the last column in each row, print X, O, or nothing and then a new line
            if (j < 2) {
                switch (grid[i][j]) {
                    case X:
                        cout << "X|";
                        break;
                    case O:
                        cout << "O|";
                        break;
                    default:
                        cout << " |";
                }
            } else {
                switch (grid[i][j]) {
                    case X:
                        cout << "X" << endl;
                        break;
                    case O:
                        cout << "O" << endl;
                        break;
                    default:
                        cout << " " << endl;
                }
            }
        }

        // after each row, print a line to show boxes
        if (i < 2) {
            cout << "-----" << endl;
        }

    }

    // used for display purposes
    cout << endl;

}


// method makes a move for the CPU and updates the grid
void CPU_move(char grid[3][3]) {

    // print "thinking" message
    cout << "CPU is thinking..." << endl;

    // wait a couple seconds
    sleep(2);

    // check to see if CPU has 2 in a row somewhere to win
    if (find_row(grid, O)) return;
    if (find_column(grid, O)) return;
    if (find_diagonal(grid, O)) return;

    // check to see if user has 2 in a row somewhere to defend
    if (find_row(grid, X)) return;
    if (find_column(grid, X)) return;
    if (find_diagonal(grid, X)) return;
    
    // if nothing detected, play in random available spot
    while (1) {
        int row = rand() % 3;
        int col = rand() % 3;

        if (grid[row][col] == EMPTY) {
            grid[row][col] = O;
            break;
        }
    }
}


// method checks the rows for 2 X's or 2 O's
int find_row(char grid[3][3], int check) {

    // iterate through rows (i = rows)
    for (int i = 0; i < 3; ++i) {

        // set a count variable for each row
        int count = 0;

        // iterate through each column (j = cols)
        for (int j = 0; j < 3; ++j) {

            // if current box is a X or O (depending on check argument), increment count
            if (grid[i][j] == check) count++;

        }

        // if 2 X's or O's were found in the row, place an O in the row if the third spot if empty
        if (count == 2) {

            // iterate through columns (j = cols)
            for (int j = 0; j < 3; ++j) {

                // if current spot is empty, set to 0 and return FOUND
                if (grid[i][j] == EMPTY) {

                    grid[i][j] = O;
                    return FOUND;

                }

            }

        }

    }

    // if no spot was found, return NOT_FOUND
    return NOT_FOUND;
}


// method checks the columns for 2 X's or 2 O's
int find_column(char grid[3][3], int check) {

    // iterate through columns (i = cols)
    for (int i = 0; i < 3; ++i) {

        // set a count variable for each column (j = cols)
        int count = 0;

        // iterate through rows (j = rows)
        for (int j = 0; j < 3; ++j) {

            // if current spot is equal to X or O (depending on check argument), increment count
            if (grid[j][i] == check) count++;

        }

        // if 2 X's or O's were found in column, place an O in the column if the third spot if empty
        if (count == 2) {

            // iterate through rows (j = rows)
            for (int j = 0; j < 3; ++j) {

                // if current spot is empty, set to O and return FOUND
                if (grid[j][i] == EMPTY) {

                    grid[j][i] = O;
                    return FOUND;

                }

            }

        }

    }

    // if no spot was found, return NOT_FOUND
    return NOT_FOUND;
}


// method checks the diagonals for 2 X's or 2 O's
int find_diagonal(char grid[3][3], int check) {

    // set count variable for diagonal
    int count = 0;

    // iterate through diagonal from top left to bottom right
    for (int i = 0; i < 3; ++i) {

        // if current spot is equal to X or O (depending on check argument), increment count
        if (grid[i][i] == check) count++;

    }

    // if 2 X's or O's were found in diagonal, place an O in the diagonal if the third spot if empty
    if (count == 2) {

        // iterate through diagonal again
        for (int i = 0; i < 3; ++i) {

            // if spot is empty, set to 0 and return FOUND
            if (grid[i][i] == EMPTY) {

                grid[i][i] = O;
                return FOUND;

            }

        }

    }


    // reassign count variable to 0
    count = 0;

    // iterate through diagonal from top right to bottom left
    for (int i = 0; i < 3; ++i) {

        // if current spot is equal to X or O (depending on check argument), increment count
        if (grid[i][2 - i] == check) {
            count++;
        }

    }

    // if 2 X's or O's were found in diagonal, place an O in the diagonal if the third spot if empty
    if (count == 2) {

        // iterate through diagonal again
        for (int i = 0; i < 3; ++i) {

            // if spot is empty, set to 0 and return FOUND
            if (grid[i][2 - i] == EMPTY) {

                grid[i][2 - i] = O;
                return FOUND;
                
            }

        }

    }

    // if no spot was found, return NOT_FOUND
    return NOT_FOUND;
}


// method checks if user or CPU has won via the diagonals and returns who won
int check_diagonals(char grid[3][3]) {

    // assign check to upper left value
    char check = grid[0][0];

    // check middle and bottom right, if necessary
    for (int i = 1; i < 3; ++i) {
        
        // if box is empty, exit loop, no winner
        if (check == EMPTY) break;

        // if box is different than last checked, exit loop, no winner
        if (grid[i][i] != check) break;

        // if someone has won, return who won
        if (i == 2) {
            if (check == X) {
                return PLAYER_WINS;
            } else {
                return CPU_WINS;
            }
        }

    }

    // reassign check to upper right value
    check = grid[0][2];

    // check middle and bottom left, if necessary
    for (int i = 1; i < 3; ++i) {
        
        // if box is empty, exit loop, no winner
        if (check == EMPTY) break;

        // if box is different than last checked, exit loop, no winner
        if (grid[i][2 - i] != check) break;

        // if someone has won, return who won
        if (i == 2) {
            if (check == X) {
                return PLAYER_WINS;
            } else {
                return CPU_WINS;
            }
        }

    }

    // return value if neither user nor CPU has won
    return 0;
}


// method checks if user or CPU has won via the rows and returns who won
int check_rows(char grid[3][3]) {

    // check each row (i = rows)
    for (int i = 0; i < 3; ++i) {
        
        // assign check to first value in row
        char check = grid[i][0];

        // if box is empty, check next row
        if (check == EMPTY) continue;

        // check middle and right columns (j = cols)
        for (int j = 1; j < 3; ++j) {

            // if current box is different than last, check next row
            if (grid[i][j] != check) break;

            // if someone has won, return who won
            if (j == 2) {
                if (check == X) {
                    return PLAYER_WINS;
                } else {
                    return CPU_WINS;
                }
            }
        }
    }

    // return value if neither user nor CPU has won
    return 0;
}


// method checks if user or CPU has won via the columns and returns who won
int check_cols(char grid[3][3]) {

    // check each column (i = cols)
    for (int i = 0; i < 3; ++i) {
        
        // assign check to first value in each column
        char check = grid[0][i];

        // if box is empty, check next column
        if (check == EMPTY) continue;

        // check middle and bottoms rows (j = rows)
        for (int j = 1; j < 3; ++j) {

            // if box is empty, check next column
            if (grid[j][i] != check) break;

            // if someone has won, return who won
            if (j == 2) {
                if (check == X) {
                    return PLAYER_WINS;
                } else {
                    return CPU_WINS;
                }
            }
        }
    }

    // return value if neither user nor CPU has won
    return 0;
}


// method checks if every spot in grid is taken, tie game
int check_full(char grid[3][3]) {

    // check each row (i = rows)
    for (int i = 0; i < 3; ++i) {
        
        // check each col (j = cols)
        for (int j = 0; j < 3; ++j) {

            // if there is an empty spot on grid still, return
            if (grid[i][j] == EMPTY) return 0;

        }

    }

    // return value if board is full, tie game
    return TIE;
}


// method prints message for who won and thanks for playing
void game_over(int winner) {
    
    if (winner == PLAYER_WINS) {
        cout << "Congratulations, you won!!!" << endl;
    } else if (winner == CPU_WINS) {
        cout << "You lost, better luck next time." << endl;
    } else {
        cout << "It's a tie." << endl;
    }

    cout << "Thanks for playing!" << endl;
    cout << endl;
}


#endif

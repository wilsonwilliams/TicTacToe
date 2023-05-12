#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "tictactoe.hpp"

// no need to reference std::cout, std::cin, etc
using namespace std;


int main() {

    // grid is the tic tac toe board
    // initialize with empty values
    char grid[3][3] = {
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY}
    };

    // declare input, row, col, turn variables
    string in_row;
    string in_col;
    char row;
    char col;
    int turn = 1;

    while (1) {

        // print what turn it is for the user
        cout << "Turn #" << turn << endl << endl;

        // show the current status of the board
        draw_grid(grid);

        // ask the user what row they want to play in and store it in input row variable
        cout << "Which row would you like to play in? (1, 2, 3): ";
        cin >> in_row;

        // store first character in input in row variable
        row = in_row[0];

        // ask the user what column they want to play in and store it in input col variable
        cout << "Which column would you like to play in? (1, 2, 3): ";
        cin >> in_col;

        // store first character in input in col variable
        col = in_col[0];

        /*check for valid row and column input
        * check if length of inputs were both 1 (valid row and column)
            * .length and .size both work for strings
        * 49 is ascii value for 1
        * 51 is ascii value for 3
        */
        if (row < 49 || row > 51 || col < 49 || col > 51 || in_row.length() != 1 || in_col.size() != 1) {

            // if invalid input, display error message and ask again
            cout << endl << "Please enter a valid row and column. Try again..." << endl << endl;
            continue;
        }

        // convert row and col inputs to numbers between 0-2 to use for indexing
        row -= 49;
        col -= 49;

        // check if the chosen spot on board is currently empty
        if (grid[row][col] != EMPTY) {

            // if already taken, display message and ask for inputs again
            cout << endl << "This spot is already taken. Choose again." << endl << endl;
            continue;
        }

        // increment turn variable
        turn++;

        // set requested location in grid to player spot
        grid[row][col] = X;
        cout << endl;

        // display board again
        draw_grid(grid);

        // checks if the user has won the game
        if (check_diagonals(grid) == PLAYER_WINS || check_rows(grid)  == PLAYER_WINS || check_cols(grid) == PLAYER_WINS) {

            // if the user has won, display winning message and exit game
            game_over(PLAYER_WINS);
            break;
        }

        // checks if the board is full - no more places to play
        if (check_full(grid) == TIE) {

            // if board is full, display message and exit game
            game_over(TIE);
            break;
        }

        // CPU's turn
        CPU_move(grid);
        cout << endl;

        // check if the CPU has won the game
        if (check_diagonals(grid) == CPU_WINS || check_rows(grid) == CPU_WINS || check_cols(grid) == CPU_WINS) {

            // if the CPU has won, display board and message then exit game
            draw_grid(grid);
            game_over(CPU_WINS);
            break;
        }

        // check if the board is full - no more places to play
        if (check_full(grid) == TIE) {

            // if board if full, display board and message then exit game
            draw_grid(grid);
            game_over(TIE);
            break;
        }

        // leave empty lines - used for display between turns
        cout << endl << endl;

    }

    return 0;
}

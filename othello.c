//***************************************************
// Filename: othello.c
//
// Author(s): 
//***************************************************

#include "othello.h"


// Constructs and returns a string representation of the board
char *toString(int size, char board[][size])
{
	char *str = (char *) calloc(3 * (size+1) * (size+1), sizeof(char));
	char *ptr = str;

	for (int i = 0; i < size; i++) {
		ptr += sprintf(ptr,(i == 0 ? "%3d" : "%2d"),i+1);
	}
	sprintf(ptr,"\n");
	ptr++;

	for (int i = 0; i < size; i++) {
		sprintf(ptr,"%1d",i+1);
		ptr++;
		for (int j = 0; j < size; j++) {
			sprintf(ptr,"%2c",board[i][j]);
			ptr += 2;
		}
		sprintf(ptr,"\n");
		ptr++;
	}

	return str;
}

// Initializes the board with start configuration of discs (see project specs)
void initializeBoard(int size, char board[][size])
{
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			board[i][j] = EMPTY;
		}
	}
	//Init starting board discs (SIZE = 8 ONLY)
	board[size/2 - 1][size/2 - 1] = BLACK;
	board[size/2 - 1][size/2] = WHITE;
	board[size/2][size/2 - 1] = WHITE;
	board[size/2][size/2] = BLACK;

}

// Returns true if moving the disc to location row,col is valid; false otherwise
bool isValidMove(int size, char board[][size], int row, int col, char disc)
{
	//condition that checks if the tile is already 'full'
	if(board[row][col] != '-') {
		return false;
	}
	//Check up side of opposite disc
	if(col - 1 >= 0) {
		if(board[row][col] == EMPTY) {
			int i = col - 1;
			while(i >= 0) {
				if(board[row][i] != EMPTY) {
					if(board[row][i] == disc) {
						return true;
					}
				} else {
					i = 0;
				}
				i--;
			}	
		}
	}
	//FIXME: UP DOWN LOOPS
	//Check right side 
        if(row + 1 >= 0) {
                if(board[row][col] == EMPTY) {
                        int i = col + 1;
                        while(i <= 8) {
                                if(board[row][i] != EMPTY) {
                                        if(board[row][i] == disc) {
                                                return true;
                                        }
                                } else {
                                        i = 0;
                                }
                                i++;
                        }       
                }
        }
        //Check up side for opposite disc
        if(row - 1 >= 0) {
                if(board[row][col] == EMPTY) {
                        int i = row - 1;
                        while(i >= 0) {
                                if(board[i][col] != EMPTY) {
                                        if(board[i][col] == disc) {
                                                return true;
                                        }
                                } else {
                                        i = 0;
                                }
                                i--;
                        }       
                }
        }


	//Check up for opposite disc
	if(row - 1 >= 0) {
		if(board[row-1][col] != EMPTY && board[row-1][col] != disc) {
			//Potential move found on up side
		}
	}
	//Check down for opposite disc
	if(row + 1 <= 8) {
		if(board[row+1][col] != EMPTY && board[row+1][col] != disc) {
			//Potential move found on down side
		}
	}
	//Check UP LEFT
	if(board[row-1][col-1] != EMPTY && board[row-1][col-1] != disc) {
		//Potential move found UP LEFT
	}
	//Check UP RIGHT
	if(board[row-1][col+1] != EMPTY && board[row-1][col-1] != disc) {
                //Potential move found UP LEFT
        }
	//Check DOWN LEFT
	if(board[row+1][col-1] != EMPTY && board[row-1][col-1] != disc) {
                //Potential move found UP LEFT
        }
	//Check DOWN RIGHT
	if(board[row+1][col-1] != EMPTY && board[row-1][col-1] != disc) {
                //Potential move found UP LEFT
        }

	//Check recursively UP, DOWN, LEFT, RIGHT, and DIAGONALS(x|y || +|-)
	return false;	// REPLACE THIS WITH YOUR IMPLEMENTATION
}

// Places the disc at location row,col and flips the opponent discs as needed
void placeDiscAt(int size, char board[][size], int row, int col, char disc)
{
	if (!isValidMove(size,board,row,col,disc)) {
		return;
	} else {
		//Place requested piece by user if valid
		board[row][col] = disc;
		//Place recursive pieces matched by game logic
		//Check left
		//Check right
		//Check up
		//Check down
		//Check diagonal UP left DOWN right '\'
		//Check diagonal UP right DOWN left '/'
	}
	
}

// Returns true if a valid move for disc is available; false otherwise
bool isValidMoveAvailable(int size, char board[][size], char disc)
{
	return true;	// REPLACE THIS WITH YOUR IMPLEMENTATION
}

// Returns true if the board is fully occupied with discs; false otherwise
bool isBoardFull(int size, char board[][size])
{
	return false;	// REPLACE THIS WITH YOUR IMPLEMENTATION	
}

// Returns true if either the board is full or a valid move is not available for either disc; false otherwise
bool isGameOver(int size, char board[][size])
{
	return false;	// REPLACE THIS WITH YOUR IMPLEMENTATION
}

// If there is a winner, it returns the disc (BLACK or WHITE) associated with the winner.
// In case of a tie, it returns TIE. When called before the game is over, it returns 0.
char checkWinner(int size, char board[][size])
{
	if (!isGameOver(size,board)) {
		return 0;
	}

	return TIE;	// REPLACE THIS WITH YOUR IMPLEMENTATION
}

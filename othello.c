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
	//Keep row and col param vars unchanged
	int origin_R = row;
	int origin_C = col;
	//condition that checks if the tile is already 'full'
	if(board[row][col] != EMPTY) {
		return false;
	}
	//Check each direction for potential moves {N, E, S, W, NE, NW, SE, SW}
	bool oppositedisc = false;
	bool matchingdisc = false;
	//Left check
	for(int a = col; a >= 0; a--) {
		if(board[row][a] != disc && !matchingdisc) {
			oppositedisc = true;
		}
		if(oppositedisc && board[row][a] == disc) {
			matchingdisc = true;
		}
		if(oppositedisc && matchingdisc) {
			return true;
		}
		
	}
	//Right check
	oppositedisc = false;
	matchingdisc = false;
	for(int b = col; b <= size; b++) {
		if(board[row][b] != disc && !matchingdisc) {
			oppositedisc = true;
		}
		if(oppositedisc && board[row][b] == disc) {
			matchingdisc = true;
		}
		if(oppositedisc && matchingdisc) {
			return true;
		}
	}
	//Up check
	oppositedisc = false;
	matchingdisc = false;
	for(int c = row; c >= 0; c--) {
		if(board[c][col] != disc && !matchingdisc) {
			oppositedisc = true;
		}
		if(oppositedisc && board[c][col] == disc) {
			matchingdisc = true;
		}
		if(oppositedisc && matchingdisc) {
			return true;
		}
	}
	//Down check
	oppositedisc = false;
	matchingdisc = false;
	for(int d = row; d <= 8; d++) {
		if(board[d][col] != disc && !matchingdisc) {
			oppositedisc = true;
		}
		if(oppositedisc && board[d][col] == disc) {
			matchingdisc = true;
		}
		if(oppositedisc && matchingdisc) {
			return true;
		}
	}
	//Backslash: +
	oppositedisc = false;
	matchingdisc = false;
	for(int e = row; e <= 8; e++) {
		for(int f = col; f <= 8; f++) {
			if(board[d][col] != disc && !matchingdisc) {
			oppositedisc = true;
			}
			if(oppositedisc && board[d][col] == disc) {
				matchingdisc = true;
			}
			if(oppositedisc && matchingdisc) {
				return true;
			}
		}
	}
	//Backslash: -
	oppositedisc = false;
	matchingdisc = false;
	for(int g = row; g >= 0; g--) {
		for(int h = col; h >= 0; h--) {
			if(board[g][h] != disc && !matchingdisc) {
			oppositedisc = true;
			}
			if(oppositedisc && board[g][h] == disc) {
				matchingdisc = true;
			}
			if(oppositedisc && matchingdisc) {
				return true;
			}
		}
	}
	//Forwardslash: +
	oppositedisc = false;
	matchingdisc = false;
	for(int g = row; g >= 0; g--) {
		for(int h = col; h <= 8; h++) {
			if(board[g][h] != disc && !matchingdisc) {
			oppositedisc = true;
			}
			if(oppositedisc && board[g][h] == disc) {
				matchingdisc = true;
			}
			if(oppositedisc && matchingdisc) {
				return true;
			}
		}
	}
	//Forwardslash: -
	for(int i = row; i <= 8; i++) {
		for(int j = col; j >= 0; j--) {
			if(board[i][j] != disc && !matchingdisc) {
			oppositedisc = true;
			}
			if(oppositedisc && board[i][j] == disc) {
				matchingdisc = true;
			}
			if(oppositedisc && matchingdisc) {
				return true;
			}
		}
	}
	//FIXME: TEST FUNC AND MAKE PLACE DISC
	return false;
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
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			if(board[i][j] == EMPTY) {
				return false;
			}
		}
	}
	return true;	
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

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
	//Init starting board discs
	board[size/2 - 1][size/2 - 1] = BLACK;
	board[size/2 - 1][size/2] = WHITE;
	board[size/2][size/2 - 1] = WHITE;
	board[size/2][size/2] = BLACK;

}
/*
	Static functions used for each direction for use in placeDiscAt() and isValidMove()
	
*/
//Up direction
static bool up_direction(int size, char board[][size], int row, int col, char disc) {
	bool oppositedisc = false;
	bool matchingdisc = false;
	for(int i = row; i >= 0; i--) {
		if(board[i][col] == EMPTY && i != row) {
			return false;
		}
		if(board[i][col] != disc && !matchingdisc && board[i][col] != EMPTY) {
			oppositedisc = true;
		}
		if(oppositedisc && board[i][col] == disc) {
			matchingdisc = true;
		}
		if(oppositedisc && matchingdisc) {
			return true;
		}
	}
	return false;
}
//Left direction
static bool left_direction(int size, char board[][size], int row, int col, char disc) {
	bool oppositedisc = false;
	bool matchingdisc = false;
	for(int a = col; a >= 0; a--) {
		if(board[row][a] == EMPTY && a != col) {
			return false;
		}
		if(board[row][a] != disc && !matchingdisc && board[row][a] != EMPTY) {
			oppositedisc = true;
		}
		if(oppositedisc && board[row][a] == disc) {
			matchingdisc = true;
		}
		if(oppositedisc && matchingdisc) {
			return true;
		}
		
	}
	return false;
}
//Right direction
static bool right_direction(int size, char board[][size], int row, int col, char disc) {
	bool oppositedisc = false;
	bool matchingdisc = false;

	for(int b = col; b <= size; b++) {
		if(board[row][b] == EMPTY && b != col) {
			return false;
		}
		
		if(board[row][b] != disc && !matchingdisc && board[row][b] != EMPTY) {
			oppositedisc = true;
		}
		if(oppositedisc && board[row][b] == disc) {
			matchingdisc = true;
		}
		
		if(oppositedisc && matchingdisc) {
			return true;
		}
	}
	return false;
}
//Down directions
static bool down_direction(int size, char board[][size], int row, int col, char disc) {
	bool oppositedisc = false;
	bool matchingdisc = false;
	for(int d = row; d <= size; d++) {
		if(board[d][col] == EMPTY && d != row) {
			return false;
		}
		if(board[d][col] != disc && !matchingdisc && board[d][col] != EMPTY) {
			oppositedisc = true;
		}
		if(oppositedisc && board[d][col] == disc) {
			matchingdisc = true;
		}
		if(oppositedisc && matchingdisc) {
			return true;
		}
	}
	return false;
}
//Backslash +
static bool backsl_plus_direction(int size, char board[][size], int row, int col, char disc) {
	bool oppositedisc = false;
	bool matchingdisc = false;
	bool stopcondition = false;
	int f = col;
	for(int e = row; !stopcondition; e++) {
		if(e <= size || f >= 0) {
			stopcondition = true;
			break;
		}
		if(board[e][f] != disc && !matchingdisc) {
			oppositedisc = true;
		}
		if(oppositedisc && board[e][f] == disc) {
			matchingdisc = true;
		}
		if(oppositedisc && matchingdisc) {
			return true;
		}
		f++;
		
	}
	return false;
}
//Backslash -
static bool backsl_neg_direction(int size, char board[][size], int row, int col, char disc) {
	bool oppositedisc = false;
	bool matchingdisc = false;
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
	return false;
}
//Forwardslash +
static bool forsl_plus_direction(int size, char board[][size], int row, int col, char disc) {
	bool oppositedisc = false;
	bool matchingdisc = false;
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
	return false;
}
//Forwardslash -
static bool forsl_neg_direction(int size, char board[][size], int row, int col, char disc) {
	bool oppositedisc = false;
	bool matchingdisc = false;
	for(int i = row; i <= 8; i++) {
		for(int j = col; j >= 0; j--) {
			
			if(board[i][j] != disc && !matchingdisc && board[i][j] != EMPTY) {
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
	return false;
}


// Returns true if moving the disc to location row,col is valid; false otherwise
bool isValidMove(int size, char board[][size], int row, int col, char disc)
{
	
	//condition that checks if the tile is already 'full'
	if(board[row][col] != EMPTY) {
		return false;
	}
	//Use static direction functions to check if a valid move is available at row, col
	if(left_direction(size, board, row, col, disc)) {
		//printf("I got my diamond tester...ICE\n");
		return true;
	}
	//Right check
	if(right_direction(size, board, row, col, disc)) {
		//printf("I got my qmond tester...ICE\n");
		return true;
	}
	//Up check
	if(up_direction(size, board, row, col, disc)) {
		//printf("I got my dgdmond tester...ICE\n");
		return true;
	}
	//Down check
	if(down_direction(size, board, row, col, disc)) {
		//printf("I got my ddsmond tester...ICE\n");
		return true;
	}
	/*
	//Backslash: +
	if(backsl_plus_direction(size, board, row, col, disc)) {
		printf("I got my dfdond tester...ICE\n");
		return true;
	}
	//Backslash: -
	if(backsl_neg_direction(size, board, row, col, disc)) {
		printf("I got my didsfaond tester...ICE\n");
		return true;
	}
	//Forwardslash: +
	if(forsl_plus_direction(size, board, row, col, disc)) {
		printf("I got my diaSGnd tester...ICE\n");
		return true;
	}
	//FIXME: FORSLASHNEG
	Forwardslash: -
	if(forsl_neg_direction(size, board, row, col, disc)) {
		printf("I got my SHmond tester...ICE\n");
		return true;
	} */
	
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
		//Check each direction and find what directions must be 'flipped'
		if(left_direction(size, board, row, col, disc)) {
			//Recursively place pieces until disc found
			bool done = false;
			int i = col - 1;
			while(!done || i <=0) {
				if(board[row][i] == disc) {
					done = true;
				} else {
					board[row][i] = disc;
				}
				i--;
				
			}
			
		}
		//Right check
		if(right_direction(size, board, row, col, disc)) {
			//Recursively place pieces until disc found
			bool done = false;
			int i = col + 1;
			while(!done || i >= size) {
				if(board[row][i] == disc) {
					done = true;
				} else {
					board[row][i] = disc;
				}
				i++;
				
			}
		}
		//Up check
		if(up_direction(size, board, row, col, disc)) {
			//Recursively place pieces until disc found
			bool done = false;
			int i = row - 1;
			while(!done || i <= 0) {
				if(board[i][col] == disc) {
					done = true;
				} else {
					board[i][col] = disc;
				}
				i--;
				
			}
		}
		//Down check
		if(down_direction(size, board, row, col, disc)) {
			//Recursively place pieces until disc found
			bool done = false;
			int i = row + 1;
			while(!done || i >= size) {
				if(board[i][col] == disc) {
					done = true;
				} else {
					board[i][col] = disc;
				}
				i++;
				
			}
		}
		//Backslash: +
		if(backsl_plus_direction(size, board, row, col, disc)) {
			//Recursively place pieces until disc found
			
		}
		//Backslash: -
		if(backsl_neg_direction(size, board, row, col, disc)) {
			//Recursively place pieces until disc found
			
		}
		//Forwardslash: +
		if(forsl_plus_direction(size, board, row, col, disc)) {
			//Recursively place pieces until disc found
			
		}

		//Forwardslash: -
		if(forsl_neg_direction(size, board, row, col, disc)) {
			//Recursively place pieces until disc found
			
		}
		

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
	//Checks for empty tiles, if none then return true
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

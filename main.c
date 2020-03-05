/*
 Names: John-Paul Powers, Trent Bultsma
 Date: 3/14/20
 Class: CS145A
 Assignment: Lab #5 (Towers of Hanoi)
 This program solves the classic "Towers of Hanoi" problem using recursion.
 BONUS: Solution is displayed with ASCII graphics in the console.
 Enjoy!!!
*/

#include <stdio.h>
// How many disks to be used in the problem
const int SIZE = 3;

// Prints the game board
void printGame(int game[3][SIZE])
{
	// Creating the three peg tips as a char array
	char top[(SIZE*2)+2];
	top[(SIZE*2)+1] = '\0';
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < (SIZE*2)+1; j++)
		{
			if(j == SIZE) top[j] = '|';
			else top[j] = ' ';
		}
	}

	// Setting up the middle sections as char arrays
	char peg1[(SIZE*2)+2];
	char peg2[(SIZE*2)+2];
	char peg3[(SIZE*2)+2];
	peg1[(SIZE*2)+1] = '\0';
	peg2[(SIZE*2)+1] = '\0';
	peg3[(SIZE*2)+1] = '\0';

	// Setting up the base of the game board as a char array
	char bottom[((SIZE+1)*6)];
	bottom[((SIZE+1)*6)-1] = '\0';
	for(int i = 0; i < ((SIZE+1)*6)-1; i++) bottom[i] = '=';
	
	// Creating and printing the board and its contents
	printf("%s %s %s\n", top, top, top);
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < (SIZE*2)+1; j++)
		{
			if(j == SIZE) peg3[j] = '|';
			else peg3[j] = ' ';
		}
		for(int j = 0; j < (SIZE*2)+1; j++)
		{
			if(j >= (SIZE - game[0][SIZE-1-i]) && j < (SIZE + game[0][SIZE-1-i]+1) && game[0][SIZE-1-i] != 0) peg1[j] = '@';
			else if(j == (SIZE - game[0][SIZE-1-i])) peg1[j] = '|';
			else peg1[j] = ' ';

			if(j >= (SIZE - game[1][SIZE-1-i]) && j < (SIZE + game[1][SIZE-1-i]+1) && game[1][SIZE-1-i] != 0) peg2[j] = '@';
			else if(j == (SIZE - game[1][SIZE-1-i])) peg2[j] = '|';
			else peg2[j] = ' ';

			if(j >= (SIZE - game[2][SIZE-1-i]) && j < (SIZE + game[2][SIZE-1-i]+1) && game[2][SIZE-1-i] != 0) peg3[j] = '@';
			else if(j == (SIZE - game[2][SIZE-1-i])) peg3[j] = '|';
			else peg3[j] = ' ';
		}
		printf("%s %s %s\n", peg1, peg2, peg3);
	}
	printf("%s\n\n", bottom);
}

// Returns the index of the spare peg (The peg that isn't the source or the target)
int getSpare(int src, int trg)
{
	if(src != trg) 
	{
		for(int i = 0; i < 3; i++)
		{
			if(src != i && trg != i) 
			{
				return i;
			}
		}
	}
	return -1;
}

// Returns the lowest space available on a peg, or -1 if the peg is full
int getSpace(int board[3][SIZE], int peg)
{
	for(int i = 0; i < SIZE; i++)
	{
		int val = board[peg][i];
		if(val == 0) return i;
	}
	return -1;
}

// Moves any number of disks to any location
void move(int (*board)[3][SIZE], int bDisk, int tDisk, int src, int trg)
{
	int spa = getSpare(src, trg);
	// Base case: Only one disk is to be moved
	if(tDisk==bDisk)
    {
		int* saveLoc = &(*board)[src][bDisk];
		(*board)[trg][getSpace(*board, trg)] = *saveLoc;
		*saveLoc = 0;
		printGame(*board);
    }
	// Recursive case: Multiple disks must be moved
    else
    {
		int saveSpace = getSpace(*board, spa);
        move(board, bDisk+1, tDisk, src, spa);
        move(board, bDisk, bDisk, src, trg);
        move(board, saveSpace, getSpace(*board, spa)-1, spa, trg);
	}
}

// Main
int main(void) 
{	
	// Create, clear, and set-up game board
	int game[3][SIZE];
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			if(i==0) game[i][j] = SIZE-j;
			else game[i][j] = 0;
		}
	}
	int moves = 1;
	for(int i = 0; i < SIZE; i++) moves *= 2;
	moves--;
	printf("Solution for Towers of Hanoi with %d disks:\n", SIZE);
	printGame(game);
	
	// Start solving process by running move on starting disks
	move(&game, 0, SIZE-1, 0, 2);
	printf("Solved in %d moves. \n(P.S. The first picture shows the initial board)\n", moves);
}

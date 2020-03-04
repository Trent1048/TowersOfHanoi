#include "stdio.h"
const int SIZE = 4;

void printGame(int game[3][SIZE])
{
	for(int i = 0; i < SIZE; i++)
	{
		printf("[%d] [%d] [%d]\n", game[0][SIZE-1-i], game[1][SIZE-1-i], game[2][SIZE-1-i]);
	}
}

// returns the index of the peg that is the spare
// (the one that isn't the source or target)
int getSpare(int src, int trg)
{
	if(src != trg) {
		for(int i = 0; i < 3; i++){
			if(src != i && trg != i) {
				return i;
			}
		}
	}
	
	return -1;
}

// returns the lowest space available on a peg
// returns -1 if the peg is full
int getSpace(int (*board)[3][SIZE], int peg)
{
	//int realGame[3][SIZE] = &board;
	for(int i = 0; i < SIZE; i++)
	{
		int val = (*board)[peg][i];
		if(val==0) return i;
	}
	return -1;
}

void move(int (*board)[3][SIZE], int bDisk, int tDisk, int src, int trg)
{
	int spa = getSpare(src, trg);
    if(tDisk==bDisk)
    {
		int* saveLoc = &(*board)[src][bDisk];
		(*board)[trg][getSpace(board, trg)] = *saveLoc;
		*saveLoc = 0;
    }
    else
    {
        move(board, bDisk-1, tDisk, src, spa);
        move(board, bDisk, bDisk, src, trg);
        //What if we move dudes onto a big dude, then indexes will be wrong. Uh oh!
        move(board, bDisk, tDisk-1, spa, trg);
    }
    
}

int main(void) 
{
	int game[3][SIZE];
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			if(i==0) game[i][j] = SIZE-j;
			else game[i][j] = 0;
		}
	}
	move(&game, SIZE-1, SIZE-1, 0, 2);
	printGame(game);
}












/*
// old code for reference
void move(int bDisk, int tDisk, int src, int trg)
{
    if(tDisk==bDisk)
    {
        int save = game[src][bDisk];
        game[src][bDisk] = 0;
        game[trg][getSpace(game, trg)] = save;
    }
    else
    {
        move(bDisk-1, tDisk, src, getSpare(src, trg));
        move(bDisk, bDisk, src, trg);
        //What if we move dudes onto a big dude, then indexes will be wrong. Uh oh!
        move(bDisk, tDisk-1, getSpare(src, trg), trg);
    }
    
}
*/
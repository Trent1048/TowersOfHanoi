#include "stdio.h"
const int size = 3;

void printGame(int game[3][size])
{
	for(int i = 0; i < size; i++)
	{
		printf( "[%d] [%d] [%d]\n", game[0][size-1-i], game[1][size-1-i], game[2][size-1-i]);
	}
}

int getSpare(int src, int trg)
{
	if((src==0&&trg==1)||(trg==0&&src==1))
	{
		return 2;
	}
	else if((src==1&&trg==2)||(trg==1&&src==2))
	{
		return 0;
	}
	else if((src==0&&trg==2)||(trg==0&&src==2))
	{
		return 1;
	}
	else return -1;
}

int lowest(int (*board)[size], int peg)
{
	for(int i = 0; i < size; i++)
	{
		int val = *( *(board + peg) + i);
		if(val==0) return i;
	}
	return -1;
}

void move(int (*board)[size], int bDisk, int tDisk, int src, int trg)
{
	int spa = getSpare(src, trg);
    if(tDisk==bDisk)
    {
        int save = *( *(board + src) + bDisk);
        *( *(board + src) + bDisk) = 0;
        *( *(board + trg) + lowest(board, trg)) = save;
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
	int game[3][size];
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(i==0) game[i][j] = size-j;
			else game[i][j] = 0;
		}
	}
	int (*gamep)[size];
	gamep = game;
	move(gamep, 0, size-1, 0, 2);
}












/*
void move(int bDisk, int tDisk, int src, int trg)
{
    if(tDisk==bDisk)
    {
        int save = game[src][bDisk];
        game[src][bDisk] = 0;
        game[trg][lowest(game, trg)] = save;
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

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
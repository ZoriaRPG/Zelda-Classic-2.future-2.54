case SCRDOORD:
        ret=tmpscr->door[ri->d[0]/10000]*10000;
        break;

int get_screen_d(long index1, long index2)
{
    if(index2 < 0 || index2 > 7)
    {
        Z_scripterrlog("You were trying to reference an out-of-bounds array index for a screen's D[] array (%ld); valid indices are from 0 to 7.\n", index1);
        return 0;
    }
    
    return game->screen_d[index1][index2];
}

void set_screen_d(long index1, long index2, int val)
{
    if(index2 < 0 || index2 > 7)
    {
        Z_scripterrlog("You were trying to reference an out-of-bounds array index for a screen's D[] array (%ld); valid indices are from 0 to 7.\n", index1);
        return;
    }
    
    game->screen_d[index1][index2] = val;
}




 case SDDD:
        ret=get_screen_d((ri->d[0])/10000 + ((get_currdmap())<<7), ri->d[1] / 10000);
        break;
        
    case SDDDD:
        ret=get_screen_d(ri->d[1] / 10000 + ((ri->d[0]/10000)<<7), ri->d[2] / 10000);
        break;
        
    case SCRDOORD:
        ret=tmpscr->door[ri->d[0]/10000]*10000;
        break;
    
    
    case SCREENSTATED:
    {
        int mi =(currmap*MAPSCRSNORMAL)+currscr;
        ret=((game->maps[mi]>>((ri->d[0]/10000)))&1)?10000:0;
    }
    break;
    
    case SCREENSTATEDD:
    {
        // Gah! >:(  Screen state is stored in game->maps, which uses 128 screens per map,
        // but the compiler multiplies the map number by 136, so it has to be corrected here.
        // Yeah, the compiler could be fixed, but that wouldn't cover existing quests...
        int mi = ri->d[0] / 10000;
        mi -= 8*((ri->d[0] / 10000) / MAPSCRS);
        
        if(BC::checkMapID(mi>>7, "Game->GetScreenState") == SH::_NoError)
            ret=(game->maps[mi] >> (ri->d[1] / 10000) & 1) ? 10000 : 0;
        else
            ret=0;
            
        break;
    }

case SCREENSTATEDDD:
    {
        // Gah! >:(  Screen state is stored in game->maps, which uses 128 screens per map,
        // but the compiler multiplies the map number by 136, so it has to be corrected here.
        // Yeah, the compiler could be fixed, but that wouldn't cover existing quests...
        int mi = ri->d[1] / 10000;
        mi -= 8*((ri->d[1] / 10000) / MAPSCRS);
        
        if(BC::checkMapID(mi>>7, "Game->GetScreenState") == SH::_NoError)
            ret=(game->maps[mi] >> (ri->d[0] / 10000) & 1) ? 10000 : 0;
        else
            ret=0;
            
        break;
    }
    
       c case SCREENFLAGSD:
        ret = get_screenflags(tmpscr,vbound(ri->d[0] / 10000,0,9));
        break;
        
    case SCREENEFLAGSD:
        ret = get_screeneflags(tmpscr,vbound(ri->d[0] / 10000,0,2));
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
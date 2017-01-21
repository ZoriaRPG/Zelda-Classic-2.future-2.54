
void do_getscreenflags()
{
    long map     = (ri->d[2] / 10000) - 1;
    long scrn  = ri->d[1] / 10000;
    long flagset = ri->d[0] / 10000;
    
    if(BC::checkMapID(map, "Game->GetScreenFlags") != SH::_NoError ||
            BC::checkBounds(scrn, 0, 0x87, "Game->GetScreenFlags") != SH::_NoError ||
            BC::checkBounds(flagset, 0, 9, "Game->GetScreenFlags") != SH::_NoError)
        return;
        
    set_register(sarg1, get_screenflags(&TheMaps[map * MAPSCRS + scrn], flagset));
}

void do_getscreeneflags()
{
    long map     = (ri->d[2] / 10000) - 1;
    long scrn  = ri->d[1] / 10000;
    long flagset = ri->d[0] / 10000;
    
    if(BC::checkMapID(map, "Game->GetScreenEFlags") != SH::_NoError ||
            BC::checkBounds(scrn, 0, 0x87, "Game->GetScreenEFlags") != SH::_NoError ||
            BC::checkBounds(flagset, 0, 9, "Game->GetScreenEFlags") != SH::_NoError)
        return;
        
    set_register(sarg1, get_screeneflags(&TheMaps[map * MAPSCRS + scrn], flagset));
}

//Set Screen Flag
   case SETSCREENFLAG:
    {
        int mi2 = ri->d[0]/10000;
        mi2 -= 8*(mi2/MAPSCRS);
	    int flag = ri->d[1]/10000;
	    
        
        if(BC::checkMapID(mi2>>7, "Game->SetScreenFlag") == SH::_NoError)
			TheMaps[map * MAPSCRS + scrn].flagset |=(ri->d[2]/10000)?flag:0 
	
    }
    break;
    
    //Get Screen Flag
   case GETSCREENFLAG:
    {
        int mi2 = ri->d[0]/10000;
        mi2 -= 8*(mi2/MAPSCRS);
	    int flag = ri->d[1]/10000;
	    
        
        if(BC::checkMapID(mi2>>7, "Game->SetScreenFlag") == SH::_NoError)
		ret = TheMaps[map * MAPSCRS + scrn].flagset&flag?10000:0;
			//TheMaps[map * MAPSCRS + scrn]flagset |=(ri->d[2]/10000)?flag:0 
    }
    break;
    
//Set Screen EFlags
   case SETSCREENEFLAG:
    {
        int mi2 = ri->d[0]/10000;
        mi2 -= 8*(mi2/MAPSCRS);
	    int flag = ri->d[1]/10000;
	    
	    
	    mapscr *m
	    
	    int f=0;
    flagpos = 0;
    
    switch(flagset)
    {
    case 0:
        f = m->enemyflags&0x1F;
        break;
        
    case 1:
        f = ornextflag(m->enemyflags&32) | ornextflag(m->enemyflags&64) | ornextflag(m->flags3&4)
            | ornextflag(m->enemyflags&128)| ornextflag((m->flags2>>4)&4);
        break;
        
    case 2:
        f = ornextflag(m->flags3&128)    | ornextflag(m->flags&2)       | ornextflag((m->flags2>>4)&8)
            | ornextflag(m->flags4&16);
        break;
    }
        
        if(BC::checkMapID(mi2>>7, "Game->SetScreenFlag") == SH::_NoError)
			TheMaps[map * MAPSCRS + scrn]flagset |=(ri->d[2]/10000)?flag:0 
    }
    break;
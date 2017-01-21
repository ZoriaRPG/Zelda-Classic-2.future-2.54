case MSGC_WARP:
    {
        int dmap = grab_next_argument();
	if(dmap<0 || dmap>=MAXDMAPS)
		return;
        int screen = grab_next_argument();
	if(screen<0 || screen>=MAPSCRS) // Should this be MAPSCRSNORMAL?
		return;
	// A shifted DMap can still go past the end of the maps, so check that
	if(DMaps[dmap].map*MAPSCRS+DMaps[dmap].xoff+screen>=TheMaps.size())
        return;
	    
	tmpscr->sidewarpdmap[0] = dmap;
	tmpscr->sidewarpscr[0]  = screen;
	tmpscr->sidewarptype[0] = wtIWARP;
        Link.zstringwarp = true;
	Z_message("SCC WARP trying to warp Link to dmap, screen", dmap, screen);
        
	return true;
    }
    
    //three argsm with warp return a, b, c, d (0, 1, 2, 3)
case MSGC_WARPSQ:
    {
        int dmap = grab_next_argument();
	if(dmap<0 || dmap>=MAXDMAPS)
		return;
        int screen = grab_next_argument();
	int destsq = grab_next_argument();
	if(screen<0 || screen>=MAPSCRS) // Should this be MAPSCRSNORMAL?
		return;
	// A shifted DMap can still go past the end of the maps, so check that
	if(DMaps[dmap].map*MAPSCRS+DMaps[dmap].xoff+screen>=TheMaps.size())
        return;
	    
	tmpscr->sidewarpdmap[destsq] = dmap;
	tmpscr->sidewarpscr[destsq]  = screen;
	tmpscr->sidewarptype[destsq] = wtIWARP;
        Link.setWarpReturnSquare(vbound(destsq, 0, 3));
	Z_message("SCC WARP trying to warp Link to dmap, screen, warpdest", dmap, screen, destsq);
        
	Link.zstringwarp = true;
	return true;
    }
    
    
case MSGC_SETSCRD:
    {
	int index = grab_next_argument();
	int value = grab_next_argument();
	int di2 = ((get_currdmap())<<7) + get_currscr()-(DMaps[get_currdmap()].type==dmOVERW ? 0 : DMaps[get_currdmap()].xoff);
	set_screen_d(di2, index, value);
	return true;
    }
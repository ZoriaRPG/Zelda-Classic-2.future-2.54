
bool LinkClass::dowarp(int type, int index)
{
    if(index<0)
        return false;
        
    word wdmap=0;
    byte wscr=0,wtype=0,t=0;
    bool overlay=false;
    t=(currscr<128)?0:1;
    int wrindex = 0;
    //int lastent_org = lastentrance;
    //int lastdmap_org = lastentrance_dmap;
    bool wasSideview = (tmpscr[t].flags7 & fSIDEVIEW)!=0 && !ignoreSideview;
    
    // Drawing commands probably shouldn't carry over...
    script_drawing_commands.Clear();
    
    switch(type)
    {
    case 0:                                                 // tile warp
	setPlayLinkWarpSound(true);
        wtype = tmpscr[t].tilewarptype[index];
        wdmap = tmpscr[t].tilewarpdmap[index];
        wscr = tmpscr[t].tilewarpscr[index];
        overlay = get_bit(&tmpscr[t].tilewarpoverlayflags,index)?1:0;
        wrindex=(tmpscr->warpreturnc>>(index*2))&3;
        break;
        
    case 1:                                                 // side warp
	
	if ( getScriptedWarp() ){
		if ( getWarpEffect() != 0 ) {
			switch( getWarpEffect() ) {
				case 1: //insta warp
				wtype = wtIWARP;
				break;
				
				case 2: //insta warp with blackout
				wtype = wtIWARPBLK; 
				break;
				
				case 3:
					//insta opening wipe
				wtype = wtIWARPOPEN;
				break;
				
				case 4: 
					//insta zap
				wtype = wtIWARPZAP;
				break;
				
				case 5:
					//insta wave
				wtype = wtIWARPWAVE;
				break;
				
				case 6: //cancelwarp
				wtype = wtNOWARP;
				break;
				
				case 7: 
					//scroll warp
				wtype = wtSCROLL;
				break;
				
				default: 
				wtype = tmpscr[t].sidewarptype[index]; 
				break;
			}
		}
		else wtype = tmpscr[t].sidewarptype[index]; 
				
	}
	
	//SCC warpstuff
	//!ZoriaRPG : I had another if here, rather than else if, which is what broke warp effects in b20...!
	else if ( getSCCWarp() ){
		if ( getSCCWarpFX() != 0 ) {
			switch( getSCCWarpFX() ) {
				case 1: //insta warp
				wtype = wtIWARP;
				break;
				
				case 2: //insta warp with blackout
				wtype = wtIWARPBLK; 
				break;
				
				case 3:
					//insta opening wipe
				wtype = wtIWARPOPEN;
				break;
				
				case 4: 
					//insta zap
				wtype = wtIWARPZAP;
				break;
				
				case 5:
					//insta wave
				wtype = wtIWARPWAVE;
				break;
				
				case 6: //cancelwarp
				wtype = wtNOWARP;
				break;
				
				case 7: 
					//scroll warp
				wtype = wtSCROLL;
				break;
				
				default: 
				wtype = tmpscr[t].sidewarptype[index]; 
				break;
			}
		}
		else wtype = tmpscr[t].sidewarptype[index]; 
				
	}
	
        else wtype = tmpscr[t].sidewarptype[index];
        wdmap = tmpscr[t].sidewarpdmap[index];
        wscr = tmpscr[t].sidewarpscr[index];
        overlay = get_bit(&tmpscr[t].sidewarpoverlayflags,index)?1:0;
        wrindex=(tmpscr->warpreturnc>>(8+(index*2)))&3;
    Z_message("Warp Return is (index, warpreturnc,sum wrindex)\n", index, tmpscr->warpreturnc, wrindex);
    Z_scripterrlog("index: \n", index);
    Z_scripterrlog("tmpscr->warpreturnc: \n", tmpscr->warpreturnc);
    Z_scripterrlog("wrindex: \n", wrindex);
        break;
        
    case 2:                                                 // whistle warp
    {
        wtype = wtWHISTLE;
        int wind = whistleitem>-1 ? itemsbuf[whistleitem].misc2 : 8;
        int level=0;
        
        if(blowcnt==0)
            level = selectWlevel(0);
        else
        {
            for(int i=0; i<abs(blowcnt); i++)
                level = selectWlevel(blowcnt);
        }
        
        if(level > QMisc.warp[wind].size && QMisc.warp[wind].size>0)
        {
            level %= QMisc.warp[wind].size;
            game->set_wlevel(level);
        }
        
        wdmap = QMisc.warp[wind].dmap[level];
        wscr = QMisc.warp[wind].scr[level];
    }
    break;
    
    case 3:
        wtype = wtIWARP;
        wdmap = cheat_goto_dmap;
        wscr = cheat_goto_screen;
        break;
        
    case 4:
        wtype = wtIWARP;
        wdmap = currdmap;
        wscr = homescr-DMaps[currdmap].xoff;
        break;
    }
    
    bool intradmap = (wdmap == currdmap);
    rehydratelake(type!=wtSCROLL);
    
    switch(wtype)
    {
    case wtCAVE:
    {
        // cave/item room
        ALLOFF();
        homescr=currscr;
        currscr=0x80;
        
        if(DMaps[currdmap].flags&dmfCAVES)                                         // cave
        {
            music_stop();
            kill_sfx();
		//if ( warpsound > 0 ) sfx(warpsound); 
            
            if(tmpscr->room==rWARP)
            {
                currscr=0x81;
                specialcave = STAIRCAVE;
            }
            else specialcave = GUYCAVE;
            
            //lighting(2,dir);
            lighting(false, true);
            loadlvlpal(10);
            bool b2 = COOLSCROLL&&
                      ((combobuf[MAPCOMBO(x,y-16)].type==cCAVE)||(combobuf[MAPCOMBO(x,y-16)].type==cCAVE2)||
                       (combobuf[MAPCOMBO(x,y-16)].type==cCAVEB)||(combobuf[MAPCOMBO(x,y-16)].type==cCAVE2B)||
                       (combobuf[MAPCOMBO(x,y-16)].type==cCAVEC)||(combobuf[MAPCOMBO(x,y-16)].type==cCAVE2C)||
                       (combobuf[MAPCOMBO(x,y-16)].type==cCAVED)||(combobuf[MAPCOMBO(x,y-16)].type==cCAVE2D));
            blackscr(30,b2?false:true);
            loadscr(0,wdmap,currscr,up,false);
            loadscr(1,wdmap,homescr,up,false);
            //preloaded freeform combos
            ffscript_engine(true);
            putscr(scrollbuf,0,0,tmpscr);
            putscrdoors(scrollbuf,0,0,tmpscr);
            dir=up;
            x=112;
            y=160;
            
            if(didpit)
            {
                didpit=false;
                x=pitx;
                y=pity;
            }
            
            reset_hookshot();
            stepforward(diagonalMovement?5:6, false);
        }
        else                                                  // item room
        {
            specialcave = ITEMCELLAR;
            map_bkgsfx(false);
            kill_enemy_sfx();
            draw_screen(tmpscr,false);
            
            //unless the room is already dark, fade to black
            if(!darkroom)
            {
                darkroom = true;
                fade(DMaps[currdmap].color,true,false);
            }
            
            blackscr(30,true);
            loadscr(0,wdmap,currscr,down,false);
            loadscr(1,wdmap,homescr,-1,false);
            dontdraw=true;
            draw_screen(tmpscr);
            fade(11,true,true);
            darkroom = false;
            dir=down;
            x=48;
            y=0;
            
            // is this didpit check necessary?
            if(didpit)
            {
                didpit=false;
                x=pitx;
                y=pity;
            }
            
            reset_hookshot();
            lighting(false, true);
            dontdraw=false;
            stepforward(diagonalMovement?16:18, false);
        }
        
        break;
    }
    
    case wtPASS:                                            // passageway
    {
        map_bkgsfx(false);
        kill_enemy_sfx();
        ALLOFF();
        homescr=currscr;
        currscr=0x81;
        specialcave = PASSAGEWAY;
        byte warpscr2 = wscr + DMaps[wdmap].xoff;
        draw_screen(tmpscr,false);
        
        if(!darkroom)
            fade(DMaps[currdmap].color,true,false);
            
        darkroom=true;
        blackscr(30,true);
        loadscr(0,wdmap,currscr,down,false);
        loadscr(1,wdmap,homescr,-1,false);
        //preloaded freeform combos
        ffscript_engine(true);
        dontdraw=true;
        draw_screen(tmpscr);
        lighting(false, true);
        dir=down;
        x=48;
        
        if((homescr&15) > (warpscr2&15))
        {
            x=192;
        }
        
        if((homescr&15) == (warpscr2&15))
        {
            if((currscr>>4) > (warpscr2>>4))
            {
                x=192;
            }
        }
        
        // is this didpit check necessary?
        if(didpit)
        {
            didpit=false;
            x=pitx;
            y=pity;
        }
        
        setEntryPoints(x,y=0);
        reset_hookshot();
        dontdraw=false;
        stepforward(diagonalMovement?16:18, false);
        newscr_clk=frame;
        activated_timed_warp=false;
        stepoutindex=index;
        stepoutscr = warpscr2;
        stepoutdmap = wdmap;
        stepoutwr=wrindex;
    }
    break;
    
    case wtEXIT: // entrance/exit
    {
        ALLOFF();
        music_stop();
        kill_sfx();
	//    if ( warpsound > 0 ) sfx(warpsound); 
        blackscr(30,false);
        currdmap = wdmap;
        dlevel=DMaps[currdmap].level;
        currmap=DMaps[currdmap].map;
        init_dmap();
        update_subscreens(wdmap);
        loadfullpal();
        ringcolor(false);
        loadlvlpal(DMaps[currdmap].color);
        //lastentrance_dmap = currdmap;
        homescr = currscr = wscr + DMaps[currdmap].xoff;
        loadscr(0,currdmap,currscr,-1,overlay);
        
        if(tmpscr->flags&fDARK)
        {
            if(get_bit(quest_rules,qr_FADE))
            {
                interpolatedfade();
            }
            else
            {
                loadfadepal((DMaps[currdmap].color)*pdLEVEL+poFADE3);
            }
            
            darkroom=naturaldark=true;
        }
        else
        {
            darkroom=naturaldark=false;
        }
        
        int wrx,wry;
        
        if(get_bit(quest_rules,qr_NOARRIVALPOINT))
        {
		
		wrx=tmpscr->warpreturnx[0];
		wry=tmpscr->warpreturny[0];
		
        }
        else
        {
            wrx=tmpscr->warparrivalx;
            wry=tmpscr->warparrivaly;
        }
        
        if(((wrx>0||wry>0)||(get_bit(quest_rules,qr_WARPSIGNOREARRIVALPOINT)))&&(!(tmpscr->flags6&fNOCONTINUEHERE)))
        {
            if(dlevel)
            {
                lastentrance = currscr;
            }
            else
            {
                lastentrance = DMaps[currdmap].cont + DMaps[currdmap].xoff;
            }
            
            lastentrance_dmap = wdmap;
        }
        
        if(dlevel)
        {
            if(get_bit(quest_rules,qr_NOARRIVALPOINT))
            {
                x=tmpscr->warpreturnx[wrindex];
                y=tmpscr->warpreturny[wrindex];
            }
            else
            {
                x=tmpscr->warparrivalx;
                y=tmpscr->warparrivaly;
            }
        }
        else
        {
            x=tmpscr->warpreturnx[wrindex];
            y=tmpscr->warpreturny[wrindex];
        }
        
        if(didpit)
        {
            didpit=false;
            x=pitx;
            y=pity;
        }
        
        dir=down;
        
        if(x==0)   dir=right;
        
        if(x==240) dir=left;
        
        if(y==0)   dir=down;
        
        if(y==160) dir=up;
        
        if(dlevel)
        {
            // reset enemy kill counts
            for(int i=0; i<128; i++)
            {
                game->guys[(currmap*MAPSCRSNORMAL)+i] = 0;
                game->maps[(currmap*MAPSCRSNORMAL)+i] &= ~mTMPNORET;
            }
        }
        
        markBmap(dir^1);
        //preloaded freeform combos
        ffscript_engine(true);
        reset_hookshot();
        
        if(isdungeon())
        {
            openscreen();
            if(get_bit(extra_rules, er_SHORTDGNWALK)==0)
                stepforward(diagonalMovement?11:12, false);
            else
                // Didn't walk as far pre-1.93, and some quests depend on that
                stepforward(8, false);
        }
        else
        {
            if(!COOLSCROLL)
                openscreen();
                
            int type1 = combobuf[MAPCOMBO(x,y-16)].type; // Old-style blue square placement
            int type2 = combobuf[MAPCOMBO(x,y)].type;
            int type3 = combobuf[MAPCOMBO(x,y+16)].type; // More old-style blue square placement
            
            if((type1==cCAVE)||(type1>=cCAVEB && type1<=cCAVED) || (type2==cCAVE)||(type2>=cCAVEB && type2<=cCAVED))
            {
                reset_pal_cycling();
                putscr(scrollbuf,0,0,tmpscr);
                putscrdoors(scrollbuf,0,0,tmpscr);
                walkup(COOLSCROLL);
            }
            else if((type3==cCAVE2)||(type3>=cCAVE2B && type3<=cCAVE2D) || (type2==cCAVE2)||(type2>=cCAVE2B && type2<=cCAVE2D))
            {
                reset_pal_cycling();
                putscr(scrollbuf,0,0,tmpscr);
                putscrdoors(scrollbuf,0,0,tmpscr);
                walkdown2(COOLSCROLL);
            }
            else if(COOLSCROLL)
            {
                openscreen();
            }
        }
        
        show_subscreen_life=true;
        show_subscreen_numbers=true;
        playLevelMusic();
        currcset=DMaps[currdmap].color;
        dointro();
        setEntryPoints(x,y);
        
        for(int i=0; i<6; i++)
            visited[i]=-1;
            
        break;
    }
    
    case wtSCROLL:                                          // scrolling warp
    {
        int c = DMaps[currdmap].color;
        currmap = DMaps[wdmap].map;
        
        // fix the scrolling direction, if it was a tile or instant warp
        if(type==0 || type>=3)
        {
            sdir = dir;
        }
        
        scrollscr(sdir, wscr+DMaps[wdmap].xoff, wdmap);
        reset_hookshot();
        
        if(!intradmap)
        {
            currdmap = wdmap;
            dlevel = DMaps[currdmap].level;
            homescr = currscr = wscr + DMaps[wdmap].xoff;
            init_dmap();
            
            int wrx,wry;
            
            if(get_bit(quest_rules,qr_NOARRIVALPOINT))
            {
                if ( getScriptedWarp() ){
			setScriptedWarp(false);
			wrx=tmpscr->warpreturnx[wrindex];
			wry=tmpscr->warpreturny[wrindex];
		}
		else{
			wrx=tmpscr->warpreturnx[0];
			wry=tmpscr->warpreturny[0];
		}
            }
            else
            {
                wrx=tmpscr->warparrivalx;
                wry=tmpscr->warparrivaly;
            }
            
            if(((wrx>0||wry>0)||(get_bit(quest_rules,qr_WARPSIGNOREARRIVALPOINT)))&&(!get_bit(quest_rules,qr_NOSCROLLCONTINUE))&&(!(tmpscr->flags6&fNOCONTINUEHERE)))
            {
                if(dlevel)
                {
                    lastentrance = currscr;
                }
                else
                {
                    lastentrance = DMaps[currdmap].cont + DMaps[currdmap].xoff;
                }
                
                lastentrance_dmap = wdmap;
            }
        }
        
        if(DMaps[currdmap].color != c)
        {
            lighting(false, true);
        }
        setScriptedWarp(false);
        playLevelMusic();
        currcset=DMaps[currdmap].color;
        dointro();
    }
    break;
    
    case wtWHISTLE:                                         // whistle warp
    {
        currmap = DMaps[wdmap].map;
        scrollscr(index, wscr+DMaps[wdmap].xoff, wdmap);
        reset_hookshot();
        currdmap=wdmap;
        dlevel=DMaps[currdmap].level;
        lighting(false, true);
        init_dmap();
        
        playLevelMusic();
        currcset=DMaps[currdmap].color;
        dointro();
        action=inwind;
        int wry;
        
        if(get_bit(quest_rules,qr_NOARRIVALPOINT))
            wry=tmpscr->warpreturny[0];
        else wry=tmpscr->warparrivaly;
        
        int wrx;
        
        if(get_bit(quest_rules,qr_NOARRIVALPOINT))
            wrx=tmpscr->warpreturnx[0];
        else wrx=tmpscr->warparrivalx;
        
        Lwpns.add(new weapon((fix)(index==left?240:index==right?0:wrx),(fix)(index==down?0:index==up?160:wry),
                             (fix)0,wWind,1,0,index,whistleitem,getUID()));
        whirlwind=255;
        whistleitem=-1;
    }
    break;
    
    case wtIWARP:
    case wtIWARPBLK:
    case wtIWARPOPEN:
    case wtIWARPZAP:
    case wtIWARPWAVE:                                       // insta-warps
    {
        //for determining whether to exit cave
        int type1 = combobuf[MAPCOMBO(x,y-16)].type;
        int type2 = combobuf[MAPCOMBO(x,y)].type;
        int type3 = combobuf[MAPCOMBO(x,y+16)].type;
        
        bool cavewarp = ((type1==cCAVE)||(type1>=cCAVEB && type1<=cCAVED) || (type2==cCAVE)||(type2>=cCAVEB && type2<=cCAVED)
                         ||(type3==cCAVE2)||(type3>=cCAVE2B && type3<=cCAVE2D) || (type2==cCAVE2)||(type2>=cCAVE2B && type2<=cCAVE2D));
                         
        if(!(tmpscr->flags3&fIWARPFULLSCREEN))
        {
            //ALLOFF kills the action, but we want to preserve Link's action if he's swimming or diving -DD
            bool wasswimming = (action == swimming);
            byte olddiveclk = diveclk;
            ALLOFF();
            
            if(wasswimming)
            {
                action = swimming;
                diveclk = olddiveclk;
            }
            
            kill_sfx();
	    //! ZoriaRPG: For some reason, both pit and side warp sounds are linked (beta 20).
	    if ( getWarpSound() > 0 && getPlayLinkWarpSound() && getIsPitWarp() == false ) {
		    //getPlayLinkWarpSound() is set from ffscript.cpp -> do_warp()
		    sfx(vbound(getWarpSound(),0,MAXSFX)); 
		   // setPlayLinkWarpSound(false);
	    }
	    //What counts as a scripted warp at this point? That may be the culprit. 
	    if ( getWarpSound() > 0 && getPlayLinkWarpSound() == 0 && getScriptedWarp() !=0 && getIsPitWarp() == false ) {
		    //getPlayLinkWarpSound() is set from ffscript.cpp -> do_warp()
		    sfx(vbound(getWarpSound(),0,MAXSFX)); 
		    //setPlayLinkWarpSound(false);
	    }
	    if ( getSCCWarpSound() > 0 ) {
		sfx(vbound(getSCCWarpSound(),0,MAXSFX)); 
		setSCCWarpSound(0);
	    }
	    
	    if ( getWarpSound() > 0 && getPlayPitWarpSound() && getIsPitWarp() ) {
		    //getPlayLinkWarpSound() is set from ffscript.cpp -> do_warp()
		    sfx(vbound(getWarpSound(),0,MAXSFX)); 
		    setPlayPitWarpSound(false);
		    setIsPitWarp(false);
	    }
	    
        }
        
        if(wtype==wtIWARPZAP)
        {
            zapout();
        }
        else if(wtype==wtIWARPWAVE)
        {
            //only draw Link if he's not in a cave -DD
            wavyout(!cavewarp);
        }
        else if(wtype!=wtIWARP)
        {
            bool b2 = COOLSCROLL&&cavewarp;
            blackscr(30,b2?false:true);
        }
        
        int c = DMaps[currdmap].color;
        currdmap = wdmap;
        dlevel = DMaps[currdmap].level;
        currmap = DMaps[currdmap].map;
        init_dmap();
        update_subscreens(wdmap);
        
        ringcolor(false);
        
        if(DMaps[currdmap].color != c)
            loadlvlpal(DMaps[currdmap].color);
            
        homescr = currscr = wscr + DMaps[currdmap].xoff;
        
        lightingInstant(); // Also sets naturaldark
        
        loadscr(0,currdmap,currscr,-1,overlay);
        
	
	if ( getScriptedWarp() ) {
		x = tmpscr->warpreturnx[getWarpReturnSquare()];
		y = tmpscr->warpreturny[getWarpReturnSquare()];
	}
	else if ( getSCCWarp() ) {
		x = tmpscr->warpreturnx[getSCCWarpReturn()];
		y = tmpscr->warpreturny[getSCCWarpReturn()];
	}
	else if(didpit)
        {
            didpit=false;  //Latest thing to try to fix warp sounds *and* give pit warps a sound.
		if ( getPlayPitWarpSound() ) {
			setPlayPitWarpSound(false);
			sfx(vbound(getWarpSound(),0,MAXSFX));
		}
            x=pitx;
            y=pity;
        }
	
	else {
		x = tmpscr->warpreturnx[wrindex];
		y = tmpscr->warpreturny[wrindex];
        }
	
        if(didpit)
        {
            didpit=false;
		/*if ( getPlayPitWarpSound() ) {
			setPlayPitWarpSound(false);
			sfx(vbound(getWarpSound(),0,MAXSFX));
		}*/
            x=pitx;
            y=pity;
        }
        
        type1 = combobuf[MAPCOMBO(x,y-16)].type;
        type2 = combobuf[MAPCOMBO(x,y)].type;
        type3 = combobuf[MAPCOMBO(x,y+16)].type;
        
        if(x==0)   dir=right;
        
        if(x==240) dir=left;
        
        if(y==0)   dir=down;
        
        if(y==160) dir=up;
        
        markBmap(dir^1);
        
        if(iswater(MAPCOMBO(x,y+8)) && _walkflag(x,y+8,0) && current_item(itype_flippers))
        {
            hopclk=0xFF;
            attackclk = charging = spins = 0;
            action=swimming;
        }
        else
            action = none;
            
        //preloaded freeform combos
        ffscript_engine(true);
        
        putscr(scrollbuf,0,0,tmpscr);
        putscrdoors(scrollbuf,0,0,tmpscr);
        
        if((type1==cCAVE)||(type1>=cCAVEB && type1<=cCAVED) || (type2==cCAVE)||(type2>=cCAVEB && type2<=cCAVED))
        {
            reset_pal_cycling();
            putscr(scrollbuf,0,0,tmpscr);
            putscrdoors(scrollbuf,0,0,tmpscr);
            walkup(COOLSCROLL);
        }
        else if((type3==cCAVE2)||(type3>=cCAVE2B && type3<=cCAVE2D) || (type2==cCAVE2)||(type2>=cCAVE2B && type2<=cCAVE2D))
        {
            reset_pal_cycling();
            putscr(scrollbuf,0,0,tmpscr);
            putscrdoors(scrollbuf,0,0,tmpscr);
            walkdown2(COOLSCROLL);
        }
        else if(wtype==wtIWARPZAP)
        {
            zapin();
        }
        else if(wtype==wtIWARPWAVE)
        {
            wavyin();
        }
        else if(wtype==wtIWARPOPEN)
        {
            openscreen();
        }
        setScriptedWarp(false);
	setIsPitWarp(false);
	setSCCWarp(false);
        show_subscreen_life=true;
        show_subscreen_numbers=true;
        playLevelMusic();
        currcset=DMaps[currdmap].color;
        dointro();
        setEntryPoints(x,y);
    }
    break;
    
    
    case wtNOWARP:
    default:
	setScriptedWarp(false);
	setIsPitWarp(false);
	setSCCWarp(false);
    //setPlayPitWarpSound(false);
        didpit=false;
        update_subscreens();
        return false;
    }
    
    // Stop Link from drowning!
    if(action==drowning)
    {
        drownclk=0;
        action=none;
    }
    
    // But keep him swimming if he ought to be!
    if(action!=rafting && iswater(MAPCOMBO(x,y+8)) && (_walkflag(x,y+8,0) || get_bit(quest_rules,qr_DROWN))
            && (current_item(itype_flippers)) && (action!=inwind))
    {
        hopclk=0xFF;
        action=swimming;
    }
    
    newscr_clk=frame;
    activated_timed_warp=false;
    eat_buttons();
    
    if(wtype!=wtIWARP)
        attackclk=0;
        
    didstuff=0;
    map_bkgsfx(true);
    loadside=dir^1;
    whistleclk=-1;
    
    if(z>0 && isSideview())
    {
        y-=z;
        z=0;
    }
    else if(!isSideview())
    {
        fall=0;
    }
    
    // If warping between top-down and sideview screens,
    // fix enemies that are carried over by Full Screen Warp
    const bool tmpscr_is_sideview = isSideview();
    
    if(!wasSideview && tmpscr_is_sideview)
    {
        for(int i=0; i<guys.Count(); i++)
        {
            if(guys.spr(i)->z > 0)
            {
                guys.spr(i)->y -= guys.spr(i)->z;
                guys.spr(i)->z = 0;
            }
            
            if(((enemy*)guys.spr(i))->family!=eeTRAP && ((enemy*)guys.spr(i))->family!=eeSPINTILE)
                guys.spr(i)->yofs += 2;
        }
    }
    else if(wasSideview && !tmpscr_is_sideview)
    {
        for(int i=0; i<guys.Count(); i++)
        {
            if(((enemy*)guys.spr(i))->family!=eeTRAP && ((enemy*)guys.spr(i))->family!=eeSPINTILE)
                guys.spr(i)->yofs -= 2;
        }
    }
    
    if((DMaps[currdmap].type&dmfCONTINUE) || (currdmap==0))
    {
        if(dlevel)
        {
            int wrx,wry;
            
            if(get_bit(quest_rules,qr_NOARRIVALPOINT))
            {
                wrx=tmpscr->warpreturnx[0];
                wry=tmpscr->warpreturny[0];
            }
            else
            {
                wrx=tmpscr->warparrivalx;
                wry=tmpscr->warparrivaly;
            }
            
            if((wtype == wtEXIT)
                    || (((wtype == wtSCROLL) && !intradmap) && ((wrx>0 || wry>0)||(get_bit(quest_rules,qr_WARPSIGNOREARRIVALPOINT)))))
            {
                if(!(wtype==wtSCROLL)||!(get_bit(quest_rules,qr_NOSCROLLCONTINUE)))
                {
                    game->set_continue_scrn(homescr);
                    //Z_message("continue_scrn = %02X e/e\n",game->get_continue_scrn());
                }
                else if(currdmap != game->get_continue_dmap())
                {
                    game->set_continue_scrn(DMaps[currdmap].cont + DMaps[currdmap].xoff);
                }
            }
            else
            {
                if(currdmap != game->get_continue_dmap())
                {
                    game->set_continue_scrn(DMaps[currdmap].cont + DMaps[currdmap].xoff);
                    //Z_message("continue_scrn = %02X dlevel\n",game->get_continue_scrn());
                }
            }
        }
        else
        {
            game->set_continue_scrn(DMaps[currdmap].cont + DMaps[currdmap].xoff);
            //Z_message("continue_scrn = %02X\n !dlevel\n",game->get_continue_scrn());
        }
        
        game->set_continue_dmap(currdmap);
        lastentrance_dmap = currdmap;
        lastentrance = game->get_continue_scrn();
        //Z_message("continue_map = %d\n",game->get_continue_dmap());
    }
    
    if(tmpscr->flags4&fAUTOSAVE)
    {
        save_game(true,0);
    }
    
    if(tmpscr->flags6&fCONTINUEHERE)
    {
        lastentrance_dmap = currdmap;
        lastentrance = homescr;
    }
    
    update_subscreens();
    verifyBothWeapons();
    
    if(wtype==wtCAVE)
    {
        if(DMaps[currdmap].flags&dmfGUYCAVES)
            Z_eventlog("Entered %s containing %s.\n",DMaps[currdmap].flags&dmfCAVES ? "Cave" : "Item Cellar",
                       roomtype_string[tmpscr[1].room]);
        else
            Z_eventlog("Entered %s.",DMaps[currdmap].flags&dmfCAVES ? "Cave" : "Item Cellar");
    }
    else Z_eventlog("Warped to DMap %d: %s, screen %d, via %s.\n", currdmap, DMaps[currdmap].name,currscr,
                        wtype==wtPASS ? "Passageway" :
                        wtype==wtEXIT ? "Entrance/Exit" :
                        wtype==wtSCROLL ? "Scrolling Warp" :
                        wtype==wtWHISTLE ? "Whistle Warp" :
                        "Insta-Warp");
                        
    eventlog_mapflags();
    return true;
}
*/

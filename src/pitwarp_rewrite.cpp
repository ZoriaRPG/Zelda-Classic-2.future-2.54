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
	    if ( getWarpSound() > 0 && getPlayLinkWarpSound() !=0 && getIsPitWarp() == false ) {
		    //getPlayLinkWarpSound() is set from ffscript.cpp -> do_warp()
		    sfx(vbound(getWarpSound(),0,MAXSFX)); 
		    setPlayLinkWarpSound(false);
	    }
	    if ( getWarpSound() > 0 && getPlayLinkWarpSound() == 0 && getScriptedWarp() !=0 && getIsPitWarp() == false ) {
		    //getPlayLinkWarpSound() is set from ffscript.cpp -> do_warp()
		    sfx(vbound(getWarpSound(),0,MAXSFX)); 
		    setPlayLinkWarpSound(false);
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
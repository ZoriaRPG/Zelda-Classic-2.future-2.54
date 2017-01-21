void setlinktile(int tile, int flip, int extend, int state, int dir)
{
    switch(state)
    {
    case ls_float:
        floatspr[dir][spr_tile] = tile;
        floatspr[dir][spr_flip] = flip;
        floatspr[dir][spr_extend] = extend;
        break;
        
    case ls_swim:
        swimspr[dir][spr_tile] = tile;
        swimspr[dir][spr_flip] = flip;
        swimspr[dir][spr_extend] = extend;
        break;
        
    case ls_dive:
        divespr[dir][spr_tile] = tile;
        divespr[dir][spr_flip] = flip;
        divespr[dir][spr_extend] = extend;
        break;
        
    case ls_slash:
        slashspr[dir][spr_tile] = tile;
        slashspr[dir][spr_flip] = flip;
        slashspr[dir][spr_extend] = extend;
        break;
        
    case ls_walk:
        walkspr[dir][spr_tile] = tile;
        walkspr[dir][spr_flip] = flip;
        walkspr[dir][spr_extend] = extend;
        break;
        
    case ls_stab:
        stabspr[dir][spr_tile] = tile;
        stabspr[dir][spr_flip] = flip;
        stabspr[dir][spr_extend] = extend;
        break;
        
    case ls_pound:
        poundspr[dir][spr_tile] = tile;
        poundspr[dir][spr_flip] = flip;
        poundspr[dir][spr_extend] = extend;
        break;
        
    case ls_jump:
        jumpspr[dir][spr_tile] = tile;
        jumpspr[dir][spr_flip] = flip;
        jumpspr[dir][spr_extend] = extend;
        break;
        
    case ls_charge:
        chargespr[dir][spr_tile] = tile;
        chargespr[dir][spr_flip] = flip;
        chargespr[dir][spr_extend] = extend;
        break;
        
    case ls_cast:
        castingspr[spr_tile] = tile;
        castingspr[spr_flip] = flip;
        castingspr[spr_extend] = extend;
        break;
        
    case ls_landhold1:
        holdspr[spr_landhold][spr_hold1][spr_tile] = tile;
        holdspr[spr_landhold][spr_hold1][spr_flip] = flip;
        holdspr[spr_landhold][spr_hold1][spr_extend] = extend;
        break;
        
    case ls_landhold2:
        holdspr[spr_landhold][spr_hold2][spr_tile] = tile;
        holdspr[spr_landhold][spr_hold2][spr_flip] = flip;
        holdspr[spr_landhold][spr_hold2][spr_extend] = extend;
        break;
        
    case ls_waterhold1:
        holdspr[spr_waterhold][spr_hold1][spr_tile] = tile;
        holdspr[spr_waterhold][spr_hold1][spr_flip] = flip;
        holdspr[spr_waterhold][spr_hold1][spr_extend] = extend;
        break;
        
    case ls_waterhold2:
        holdspr[spr_waterhold][spr_hold2][spr_tile] = tile;
        holdspr[spr_waterhold][spr_hold2][spr_flip] = flip;
        holdspr[spr_waterhold][spr_hold2][spr_extend] = extend;
        break;
        
    default:
        break;
    }
}

 case MSG_START:
    {
        d->dp3=(int*)zc_malloc(sizeof(int)*4);
        p=(int*)d->dp3;
        p[lt_clock]=0;
        p[lt_tile]=0;
        p[lt_flip]=0;
        p[lt_extend]=0;
        linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], d->d2, d->d1, zinit.linkanimationstyle);
        break;
    }
    
    }

int d_ltile_proc(int msg,DIALOG *d,int c)
{
    //these are here to bypass compiler warnings about unused arguments
    c=c;
    
    //d1=dir
    //d2=type (determines how to animate)
    //fg=cset (6)
    enum {lt_clock, lt_tile, lt_flip, lt_extend};
    static int bg=makecol(0, 0, 0);
    int *p=(int*)d->dp3;
    int oldtile=0;
    int oldflip=0;
    
    switch(msg)
    {
    case MSG_START:
    {
        d->dp3=(int*)zc_malloc(sizeof(int)*4);
        p=(int*)d->dp3;
        p[lt_clock]=0;
        p[lt_tile]=0;
        p[lt_flip]=0;
        p[lt_extend]=0;
        linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], d->d2, d->d1, zinit.linkanimationstyle);
        break;
    }
    
    case MSG_CLICK:
    {
        int t;
        int f;
        int extend;
        int cs = 6;
        linktile(&t, &f, &extend, d->d2, d->d1, zinit.linkanimationstyle);
        
        switch(extend)
        {
        case 0:
            if(!isinRect(gui_mouse_x(),gui_mouse_y(),d->x+2+8, d->y+2+4, d->x+(16*(is_large+1))+8+2, d->y+(16+16*(is_large+1))+2))
            {
                return D_O_K;
            }
            
            break;
            
        case 1:
            if(!isinRect(gui_mouse_x(),gui_mouse_y(),d->x+2+8, d->y+2+4, d->x+(16*(is_large+1))+8+2, d->y+(4+32*(is_large+1))+2))
            {
                return D_O_K;
            }
            
            break;
            
        case 2:
            if(!isinRect(gui_mouse_x(),gui_mouse_y(),d->x+2+8, d->y+4, d->x+(32*(is_large+1))+8+2, d->y+(4+32*(is_large+1))+2))
            {
                return D_O_K;
            }
            
            break;
        }
        
        if(select_tile(t,f,2,cs,false,extend, true))
        {
            extend=ex;
            setlinktile(t,f,extend,d->d2,d->d1);
            return D_REDRAW;
        }
    }
    break;
    
    case MSG_VSYNC:
        oldtile=p[lt_tile];
        oldflip=p[lt_flip];
        p[lt_clock]++;
        
        switch(zinit.linkanimationstyle)
        {
        case las_original:                                             //2-frame
            switch(d->d2)
            {
            case ls_charge:
            case ls_walk:
                linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], d->d2, d->d1, zinit.linkanimationstyle);
                
                if(p[lt_clock]>=6)
                {
                    if(d->d1==up&&d->d2==ls_walk)
                    {
                        p[lt_flip]=1;                //h flip
                    }
                    else
                    {
                        p[lt_extend]==2?p[lt_tile]+=2:p[lt_tile]++;               //tile++
                    }
                };
                
                if(p[lt_clock]>=11)
                {
                    p[lt_clock]=-1;
                }
                
                break;
                
            case ls_jump:
                if(p[lt_clock]>=24)
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_walk, d->d1, zinit.linkanimationstyle);
                    
                    if(p[lt_clock]>=36)
                    {
                        p[lt_clock]=-1;
                    }
                }
                else
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_jump, d->d1, zinit.linkanimationstyle);
                    p[lt_tile]+=p[lt_extend]==2?((int)p[lt_clock]/8)*2:((int)p[lt_clock]/8);
                }
                
                break;
                
            case ls_slash:
                if(p[lt_clock]<6)
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_slash, d->d1, zinit.linkanimationstyle);
                }
                else if(p[lt_clock]<12)
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_stab, d->d1, zinit.linkanimationstyle);
                }
                else if(p[lt_clock]<13)
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_walk, d->d1, zinit.linkanimationstyle);
                }
                else
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_walk, d->d1, zinit.linkanimationstyle);
                    p[lt_extend]==2?p[lt_tile]+=2:p[lt_tile]++;                  //tile++
                    
                    if(p[lt_clock]>=16)
                    {
                        p[lt_clock]=-1;
                    }
                };
                
                break;
                
            case ls_stab:
                if(p[lt_clock]<12)
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_stab, d->d1, zinit.linkanimationstyle);
                }
                else if(p[lt_clock]<13)
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_walk, d->d1, zinit.linkanimationstyle);
                }
                else
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_walk, d->d1, zinit.linkanimationstyle);
                    p[lt_extend]==2?p[lt_tile]+=2:p[lt_tile]++;                  //tile++
                    
                    if(p[lt_clock]>=16)
                    {
                        p[lt_clock]=-1;
                    }
                };
                
                break;
                
            case ls_pound:
                if(p[lt_clock]<12)
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_pound, d->d1, zinit.linkanimationstyle);
                }
                else if(p[lt_clock]<30)
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_stab, d->d1, zinit.linkanimationstyle);
                }
                else
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_walk, d->d1, zinit.linkanimationstyle);
                    
                    if(p[lt_clock]>=31)
                    {
                        p[lt_clock]=-1;
                    }
                };
                
                break;
                
            case ls_float:
                linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_float, d->d1, zinit.linkanimationstyle);
                
                if(p[lt_clock]>=12)
                {
                    p[lt_extend]==2?p[lt_tile]+=2:p[lt_tile]++;                  //tile++
                };
                
                if(p[lt_clock]>=23)
                {
                    p[lt_clock]=-1;
                }
                
                break;
                
            case ls_swim:
                linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_swim, d->d1, zinit.linkanimationstyle);
                
                if(p[lt_clock]>=12)
                {
                    p[lt_extend]==2?p[lt_tile]+=2:p[lt_tile]++;                  //tile++
                };
                
                if(p[lt_clock]>=23)
                {
                    p[lt_clock]=-1;
                }
                
                break;
                
            case ls_dive:
                linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_dive, d->d1, zinit.linkanimationstyle);
                
                if(p[lt_clock]>=50)
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_float, d->d1, zinit.linkanimationstyle);
                };
                
                if((p[lt_clock]/12)&1)
                {
                    p[lt_extend]==2?p[lt_tile]+=2:p[lt_tile]++;                  //tile++
                };
                
                if(p[lt_clock]>=81)
                {
                    p[lt_clock]=-1;
                }
                
                break;
                
            case ls_landhold1:
                linktile(&p[lt_tile], &p[lt_flip], ls_landhold1, d->d1, zinit.linkanimationstyle);
                break;
                
            case ls_landhold2:
                linktile(&p[lt_tile], &p[lt_flip], ls_landhold2, d->d1, zinit.linkanimationstyle);
                break;
                
            case ls_waterhold1:
                linktile(&p[lt_tile], &p[lt_flip], ls_waterhold1, d->d1, zinit.linkanimationstyle);
                break;
                
            case ls_waterhold2:
                linktile(&p[lt_tile], &p[lt_flip], ls_waterhold2, d->d1, zinit.linkanimationstyle);
                break;
                
            case ls_cast:
                linktile(&p[lt_tile], &p[lt_flip], ls_cast, d->d1, zinit.linkanimationstyle);
                
                if(p[lt_clock]<96)
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_landhold2, d->d1, zinit.linkanimationstyle);
                };
                
                if(p[lt_clock]>=194)
                {
                    p[lt_clock]=-1;
                }
                
                break;
                
            default:
                break;
            }
            
            break;
            
        case las_bszelda:                                             //3-frame BS
            switch(d->d2)
            {
            case ls_charge:
            case ls_walk:
                linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], d->d2, d->d1, zinit.linkanimationstyle);
                p[lt_tile]+=anim_3_4(p[lt_clock],7)*(p[lt_extend]==2?2:1);
                
                if(p[lt_clock]>=27)
                {
                    p[lt_clock]=-1;
                }
                
                break;
                
            case ls_jump:
                if(p[lt_clock]>=24)
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_walk, d->d1, zinit.linkanimationstyle);
                    
                    if(p[lt_clock]>=36)
                    {
                        p[lt_clock]=-1;
                    }
                }
                else
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_jump, d->d1, zinit.linkanimationstyle);
                    p[lt_tile]+=p[lt_extend]==2?((int)p[lt_clock]/8)*2:((int)p[lt_clock]/8);
                }
                
                break;
                
            case ls_slash:
                if(p[lt_clock]<6)
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_slash, d->d1, zinit.linkanimationstyle);
                }
                else if(p[lt_clock]<12)
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_stab, d->d1, zinit.linkanimationstyle);
                }
                else if(p[lt_clock]<13)
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_walk, d->d1, zinit.linkanimationstyle);
                }
                else
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_walk, d->d1, zinit.linkanimationstyle);
                    p[lt_extend]==2?p[lt_tile]+=2:p[lt_tile]++;                  //tile++
                    
                    if(p[lt_clock]>=16)
                    {
                        p[lt_clock]=-1;
                    }
                };
                
                break;
                
            case ls_stab:
                if(p[lt_clock]<12)
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_stab, d->d1, zinit.linkanimationstyle);
                }
                else if(p[lt_clock]<13)
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_walk, d->d1, zinit.linkanimationstyle);
                }
                else
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_walk, d->d1, zinit.linkanimationstyle);
                    p[lt_extend]==2?p[lt_tile]+=2:p[lt_tile]++;                  //tile++
                    
                    if(p[lt_clock]>=16)
                    {
                        p[lt_clock]=-1;
                    }
                };
                
                break;
                
            case ls_pound:
                if(p[lt_clock]<12)
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_pound, d->d1, zinit.linkanimationstyle);
                }
                else if(p[lt_clock]<30)
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_stab, d->d1, zinit.linkanimationstyle);
                }
                else
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_walk, d->d1, zinit.linkanimationstyle);
                    
                    if(p[lt_clock]>=31)
                    {
                        p[lt_clock]=-1;
                    }
                };
                
                break;
                
            case ls_float:
                linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_float, d->d1, zinit.linkanimationstyle);
                p[lt_tile]+=anim_3_4(p[lt_clock],7)*(p[lt_extend]==2?2:1);
                
                if(p[lt_clock]>=55)
                {
                    p[lt_clock]=-1;
                }
                
                break;
                
            case ls_swim:
                linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_swim, d->d1, zinit.linkanimationstyle);
                p[lt_tile]+=anim_3_4(p[lt_clock],7)*(p[lt_extend]==2?2:1);
                
                if(p[lt_clock]>=55)
                {
                    p[lt_clock]=-1;
                }
                
                break;
                
            case ls_dive:
                linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_dive, d->d1, zinit.linkanimationstyle);
                
                if(p[lt_clock]>=50)
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_float, d->d1, zinit.linkanimationstyle);
                };
                
                p[lt_tile]+=anim_3_4(p[lt_clock],7)*(p[lt_extend]==2?2:1);
                
                if(p[lt_clock]>=81)
                {
                    p[lt_clock]=-1;
                }
                
                break;
                
            case ls_landhold1:
                linktile(&p[lt_tile], &p[lt_flip], ls_landhold1, d->d1, zinit.linkanimationstyle);
                break;
                
            case ls_landhold2:
                linktile(&p[lt_tile], &p[lt_flip], ls_landhold2, d->d1, zinit.linkanimationstyle);
                break;
                
            case ls_waterhold1:
                linktile(&p[lt_tile], &p[lt_flip], ls_waterhold1, d->d1, zinit.linkanimationstyle);
                break;
                
            case ls_waterhold2:
                linktile(&p[lt_tile], &p[lt_flip], ls_waterhold2, d->d1, zinit.linkanimationstyle);
                break;
                
            case ls_cast:
                linktile(&p[lt_tile], &p[lt_flip], ls_cast, d->d1, zinit.linkanimationstyle);
                
                if(p[lt_clock]<96)
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_landhold2, d->d1, zinit.linkanimationstyle);
                };
                
                if(p[lt_clock]>=194)
                {
                    p[lt_clock]=-1;
                }
                
                break;
                
            default:
                break;
            }
            
            break;
            
        case las_zelda3slow:                                         //multi-frame Zelda 3 (slow)
        case las_zelda3:                                             //multi-frame Zelda 3
            switch(d->d2)
            {
            case ls_charge:
            case ls_walk:
                linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], d->d2, d->d1, zinit.linkanimationstyle);
                
                if(p[lt_clock]>=(64*(link_animation_speed)))
                {
                    p[lt_tile]+=(p[lt_extend]==2?2:1);
                    
                    int l=((p[lt_clock]/link_animation_speed)&15);
                    l-=((l>3)?1:0)+((l>12)?1:0);
                    p[lt_tile]+=(l/2)*(p[lt_extend]==2?2:1);
                    
                    //p[lt_tile]+=(((p[lt_clock]>>2)%8)*(p[lt_extend]==2?2:1));
                    if(p[lt_clock]>=255)
                    {
                        p[lt_clock]=-1;
                    }
                }
                
                break;
                
            case ls_jump:
                if(p[lt_clock]>=24)
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_walk, d->d1, zinit.linkanimationstyle);
                    
                    if(p[lt_clock]>=36)
                    {
                        p[lt_clock]=-1;
                    }
                }
                else
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_jump, d->d1, zinit.linkanimationstyle);
                    p[lt_tile]+=p[lt_extend]==2?((int)p[lt_clock]/8)*2:((int)p[lt_clock]/8);
                }
                
                break;
                
            case ls_slash:
                if(p[lt_clock]>23)
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_slash, d->d1, zinit.linkanimationstyle);
                    p[lt_tile]+=(((p[lt_clock]>>2)%6)*(p[lt_extend]==2?2:1));
                    
                    if(p[lt_clock]>=47)
                    {
                        p[lt_clock]=-1;
                    }
                }
                else
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_walk, d->d1, zinit.linkanimationstyle);
                }
                
                break;
                
            case ls_stab:
                if(p[lt_clock]>35)
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_stab, d->d1, zinit.linkanimationstyle);
                    p[lt_tile]+=(((p[lt_clock]>>2)%3)*(p[lt_extend]==2?2:1));
                    
                    if(p[lt_clock]>=47)
                    {
                        p[lt_clock]=-1;
                    }
                }
                else
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_walk, d->d1, zinit.linkanimationstyle);
                }
                
                break;
                
            case ls_pound:
                if(p[lt_clock]>35)
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_pound, d->d1, zinit.linkanimationstyle);
                    p[lt_tile]+=(((p[lt_clock]>>2)%3)*(p[lt_extend]==2?2:1));
                    
                    if(p[lt_clock]>=47)
                    {
                        p[lt_clock]=-1;
                    }
                }
                else
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_walk, d->d1, zinit.linkanimationstyle);
                }
                
                break;
                
            case ls_float:
                linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_float, d->d1, zinit.linkanimationstyle);
                p[lt_tile]+=((p[lt_clock]/6)%4)<<(p[lt_extend]==2?1:0);
                
                if(p[lt_clock]>=23)
                {
                    p[lt_clock]=-1;
                }
                
                break;
                
            case ls_swim:
                linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_swim, d->d1, zinit.linkanimationstyle);
                p[lt_tile]+=((p[lt_clock]/12)%4)<<(p[lt_extend]==2?1:0);
                
                if(p[lt_clock]>=47)
                {
                    p[lt_clock]=-1;
                }
                
                break;
                
            case ls_dive:
                linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_dive, d->d1, zinit.linkanimationstyle);
                
                if(p[lt_clock]>=50)
                {
                    linktile(&p[lt_tile], &p[lt_flip], &p[lt_extend], ls_float, d->d1, zinit.linkanimationstyle);
                };
                
                p[lt_tile]+=((p[lt_clock]/6)%4)<<(p[lt_extend]==2?1:0);
                
                if(p[lt_clock]>=81)
                {
                    p[lt_clock]=-1;
                }
                
                break;
                
            case ls_landhold1:
                linktile(&p[lt_tile], &p[lt_flip], ls_landhold1, d->d1, zinit.linkanimationstyle);
                break;
                
            case ls_landhold2:
                linktile(&p[lt_tile], &p[lt_flip], ls_landhold2, d->d1, zinit.linkanimationstyle);
                break;
                
            case ls_waterhold1:
                linktile(&p[lt_tile], &p[lt_flip], ls_waterhold1, d->d1, zinit.linkanimationstyle);
                break;
                
            case ls_waterhold2:
                linktile(&p[lt_tile], &p[lt_flip], ls_waterhold2, d->d1, zinit.linkanimationstyle);
                break;
                
            case ls_cast:
                linktile(&p[lt_tile], &p[lt_flip], ls_cast, d->d1, zinit.linkanimationstyle);
                
                if(p[lt_clock]<96)
                {
                    linktile(&p[lt_tile], &p[lt_flip], ls_landhold2, d->d1, zinit.linkanimationstyle);
                };
                
                if(p[lt_clock]>=194)
                {
                    p[lt_clock]=-1;
                }
                
                break;
                
            default:
                break;
            }
            
            break;
            
        default:
            break;
        }
        
        if((p[lt_tile]!=oldtile)||(p[lt_flip]!=oldflip))
        {
            d->flags|=D_DIRTY;
        }
	
	
	
	case MSG_DRAW:
    {
        BITMAP *buf=create_bitmap_ex(8,1,1);
        BITMAP *buf2=buf;
        int dummy1, dummy2;
        int extend;
        linktile(&dummy1, &dummy2, &extend, d->d2, d->d1, zinit.linkanimationstyle);
        int w = 16;
        int h = 16;
        
        switch(extend)
        {
        case 0: //16x16
            break;
            
        case 1: //16x32
            w = 16;
            h = 32;
            break;
            
        case 2: //32x32
            w = 32;
            h = 32;
            break;
            
        default:
            break;
        }
        
        buf = create_bitmap_ex(8,w,h);
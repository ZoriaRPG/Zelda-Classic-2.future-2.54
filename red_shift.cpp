//red shift
        // color scale the game screen
        for(int y=0; y<168; y++)
        {
            for(int x=0; x<256; x++)
            {
                int c = framebuf->line[y+playing_field_offset][x];
                int r = zc_min(int(RAMpal[c].r*0.4 + RAMpal[c].g*0.6 + RAMpal[c].b*0.4)>>1,31);
                framebuf->line[y+playing_field_offset][x] = r+CSET(2);
            }
        }
    }
    
    blit(framebuf,scrollbuf, 0, playing_field_offset, 0, playing_field_offset, 256, 168);
    
    // set up the new palette
    for(int i=CSET(2); i < CSET(4); i++)
    {
        int r = (i-CSET(2)) << 1;
        RAMpal[i].r = r;
        RAMpal[i].g = r >> 3;
        RAMpal[i].b = r >> 4;
    }
    
    refreshpal = true;
}


void slide_in_color(int color)
{
    for(int i=1; i<16; i+=3)
    {
        RAMpal[CSET(2)+i+2] = RAMpal[CSET(2)+i+1];
        RAMpal[CSET(2)+i+1] = RAMpal[CSET(2)+i];
        RAMpal[CSET(2)+i]   = NESpal(color);
    }
    
    refreshpal=true;
}

void loadpalset(int cset,int dataset)
{
    int j = CSET(dataset)*3;
    
    for(int i=0; i<16; i++,j+=3)
    {
        RAMpal[CSET(cset)+i] = _RGB(&colordata[j]);
    }
    
    if(cset==6 && !get_bit(quest_rules,qr_NOLEVEL3FIX) && DMaps[currdmap].color==3)
        RAMpal[CSET(6)+2] = NESpal(0x37);
        
    refreshpal=true;
}
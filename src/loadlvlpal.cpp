loadlvlpal(DMaps[currdmap].color);


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

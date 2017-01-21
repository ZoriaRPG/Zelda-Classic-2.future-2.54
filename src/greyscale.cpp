//grayscale entire screen from weapons.cpp

int greyclock;

void do_greyscale();
void undo_greyscale();

extern PALETTE tempgreypal;



void do_greyscale(){
	memcpy(tempgreypal, RAMpal, PAL_SIZE*sizeof(RGB));
	if(get_bit(quest_rules,qr_FADE)) {
		for(int i=CSET(0); i < CSET(15); i++)
		{
			int g = zc_min((RAMpal[i].r*42 + RAMpal[i].g*75 + RAMpal[i].b*14) >> 7, 63);
			g = (g >> 1) + 32;
			RAMpal[i] = _RGB(g,g,g);
		}
    
	}
	else
	{
		// this is awkward. NES Z1 converts colors based on the global
		// NES palette. Something like RAMpal[i] = NESpal( reverse_NESpal(RAMpal[i]) & 0x30 );
		for(int i=CSET(0); i < CSET(15); i++)
		{
			RAMpal[i] = NESpal(reverse_NESpal(RAMpal[i]) & 0x30);
		}
	} 
	refreshpal = true;
}

void undo_greyscale(){
    memcpy(RAMpal, tempgreypal, PAL_SIZE*sizeof(RGB));
    refreshpal = true;
}

void do_greyscale(){
	if(!usebombpal){
		if(clk==misc || clk==misc+5){
                        usebombpal=true;
                        memcpy(tempbombpal, RAMpal, PAL_SIZE*sizeof(RGB));
			if(get_bit(quest_rules,qr_FADE)) {
				for(int i=CSET(0); i < CSET(15); i++)
				{
					int g = zc_min((RAMpal[i].r*42 + RAMpal[i].g*75 + RAMpal[i].b*14) >> 7, 63);
					g = (g >> 1) + 32;
					RAMpal[i] = _RGB(g,g,g);
				}
		    
			}
			else
			{
				// this is awkward. NES Z1 converts colors based on the global
				// NES palette. Something like RAMpal[i] = NESpal( reverse_NESpal(RAMpal[i]) & 0x30 );
				for(int i=CSET(0); i < CSET(15); i++)
				{
					RAMpal[i] = NESpal(reverse_NESpal(RAMpal[i]) & 0x30);
				}
			} 
			refreshpal = true;
		}
	}
	if((clk==misc+4 || clk==misc+9) && usebombpal)
	{
	    // undo grayscale
	    usebombpal=false;
	    memcpy(RAMpal, tempbombpal, PAL_SIZE*sizeof(RGB));
	    refreshpal = true;
	}
}
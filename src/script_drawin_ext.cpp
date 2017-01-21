//DrawBitmapEx(int bitmap, int sourcex, int sourcey, int sourcewidth, int sourceheight, int destx, int desty, 
//		int destw, int desth, int mode, int flip, int rotation, bool mask)
//! { "DrawBitmapEx",      typeVOID, FUNCTION, 0, 1, ARGS_14(S,F,F,F,F,F,F,F,F,F,F,F,F,F,B) },
void do_bitmapexr(BITMAP *bmp, int *sdci, int xoffset, int yoffset)
{
    //sdci[1]=layer
    //sdci[2]=bitmap
    //sdci[3]=sourcex
    //sdci[4]=sourcey
    //sdci[5]=sourcew
    //sdci[6]=sourceh
    //sdci[7]=destx
    //sdci[8]=desty
    //sdci[9]=destw
    //sdci[10]=desth
				//Don't know if these already have static values of 0, 1, 2, but even if
				//they do, I'm redefining them for ZC. 
	//scdi[11] = mode :  	0 = DRAW_SPRITE_NORMAL     - draws a masked sprite, like draw_sprite()
	//			1 = DRAW_SPRITE_LIT        - draws a tinted sprite, like draw_lit_sprite()
	//			2 = DRAW_SPRITE_TRANS  
			//The allegro docs make it seem that these have values 0, 1, 2, and 3 normally. 
			//If not, I'll fix it. 
    //scdi[12] = flip : 	DRAW_SPRITE_NO_FLIP = 0    - do not perform flipping
	//			DRAW_SPRITE_H_FLIP  = 1       - flip horizontally
		//		DRAW_SPRITE_V_FLIP  = 2      - flip vertically
	//			DRAW_SPRITE_VH_FLIP = 3       - flip both vertically and horizontally
	//sdci[13]=rotation
    //sdci[14]=mask
	
    
    int bitmapIndex = sdci[2]/10000;
    int sx = sdci[3]/10000;
    int sy = sdci[4]/10000;
    int sw = sdci[5]/10000;
    int sh = sdci[6]/10000;
    int dx = sdci[7]/10000;
    int dy = sdci[8]/10000;
    int dw = sdci[9]/10000;
    int dh = sdci[10]/10000;
    int mode = scdi[11]/10000;
    int flip = scdi[12]/10000;
    float rot = sdci[13]/10000;
    bool masked = (sdci[14] != 0);

	BITMAP *sourceBitmap = zscriptDrawingRenderTarget->GetBitmapPtr(bitmapIndex);
	if(sx >= sourceBitmap->w || sy >= sourceBitmap->h)
		return;

	sx = vbound(sx, 0, sourceBitmap->w);
	sy = vbound(sy, 0, sourceBitmap->h);
	sw = vbound(sw, 0, sourceBitmap->w - sx); //keep the w/h within range as well
	sh = vbound(sh, 0, sourceBitmap->h - sy);
        
    bool stretched = (sw != dw || sh != dh);
        
    if(!sourceBitmap)
    {
        Z_message("Warning: Screen->DrawBitmap(%d) contains invalid data or is not initialized.\n", bitmapIndex);
        return;
    }
    
    BITMAP* subBmp = 0;
    BITMAP* subBmp2 = 10; //Sub bitmap for rotation. 
    
    if(rot != 0)
    {
        subBmp = script_drawing_commands.AquireSubBitmap(dw, dh);
        
        if(!subBmp)
        {
        }
    }
    
    dx = dx + xoffset;
    dy = dy + yoffset;
    
    if(stretched)
    {
        if(masked)
        {
            if(rot != 0)
            {
                masked_stretch_blit(sourceBitmap, subBmp, sx, sy, sw, sh, 0, 0, dw, dh);
                rotate_sprite(subBmp2, subBmp, dx, dy, degrees_to_fixed(rot));
		    if ( mode <= 0 ) draw_sprite_ex(bmp, subBmp2, dx, dy, DRAW_SPRITE_NORMAL, flip);
		    if ( mode == 1 ) draw_sprite_ex(bmp, subBmp2, dx, dy, DRAW_SPRITE_TRANS, flip);
		    if ( mode >= 2 ) draw_sprite_ex(bmp, subBmp2, dx, dy, DRAW_SPRITE_LIT, flip);
            }
            else {
		  masked_stretch_blit(sourceBitmap, subBmp, sx, sy, sw, sh, 0, 0, dw, dh);  
		    if ( mode <= 0 ) draw_sprite_ex(bmp, subBmp, dx, dy, DRAW_SPRITE_NORMAL, flip);
		    if ( mode == 1 ) draw_sprite_ex(bmp, subBmp, dx, dy, DRAW_SPRITE_TRANS, flip);
		    if ( mode >= 2 ) draw_sprite_ex(bmp, subBmp, dx, dy, DRAW_SPRITE_LIT, flip);
		    
	    }
        }
        else
        {
            if(rot != 0)
            {
                stretch_blit(sourceBitmap, subBmp, sx, sy, sw, sh, 0, 0, dw, dh);
                rotate_sprite(subBmp2, subBmp, dx, dy, degrees_to_fixed(rot));
		    if ( mode <= 0 ) draw_sprite_ex(bmp, subBmp2, dx, dy, DRAW_SPRITE_NORMAL, flip);
		    if ( mode == 1 ) draw_sprite_ex(bmp, subBmp2, dx, dy, DRAW_SPRITE_TRANS, flip);
		    if ( mode >= 2 ) draw_sprite_ex(bmp, subBmp2, dx, dy, DRAW_SPRITE_LIT, flip);
		
            }
            else{
		   stretch_blit(sourceBitmap, subBmp, sx, sy, sw, sh, 0, 0, dw, dh);
			if ( mode <= 0 ) draw_sprite_ex(bmp, subBmp, dx, dy, DRAW_SPRITE_NORMAL, flip);
			if ( mode == 1 ) draw_sprite_ex(bmp, subBmp, dx, dy, DRAW_SPRITE_TRANS, flip);
			if ( mode >= 2 ) draw_sprite_ex(bmp, subBmp, dx, dy, DRAW_SPRITE_LIT, flip);
		    
	    }

        }
    }
    else
    {
        if(masked)
        {
            if(rot != 0)
            {
                masked_blit(sourceBitmap, subBmp, sx, sy, 0, 0, dw, dh);
                rotate_sprite(subBmp2, subBmp, dx, dy, degrees_to_fixed(rot));
		    if ( mode <= 0 ) draw_sprite_ex(bmp, subBmp2, dx, dy, DRAW_SPRITE_NORMAL, flip);
		    if ( mode == 1 ) draw_sprite_ex(bmp, subBmp2, dx, dy, DRAW_SPRITE_TRANS, flip);
		    if ( mode >= 2 ) draw_sprite_ex(bmp, subBmp2, dx, dy, DRAW_SPRITE_LIT, flip);
		
            }
            else{
		    masked_blit(sourceBitmap, subBmp, sx, sy, 0, 0, dw, dh);
		    if ( mode <= 0 ) draw_sprite_ex(bmp, subBmp, dx, dy, DRAW_SPRITE_NORMAL, flip);
		    if ( mode == 1 ) draw_sprite_ex(bmp, subBmp, dx, dy, DRAW_SPRITE_TRANS, flip);
		    if ( mode >= 2 ) draw_sprite_ex(bmp, subBmp, dx, dy, DRAW_SPRITE_LIT, flip);
		    
	    }
        }
        else
        {
            if(rot != 0)
            {
                blit(sourceBitmap, subBmp, sx, sy, 0, 0, dw, dh);
                rotate_sprite(subBmp2, subBmp, dx, dy, degrees_to_fixed(rot));
		    if ( mode <= 0 ) draw_sprite_ex(bmp, subBmp2, dx, dy, DRAW_SPRITE_NORMAL, flip);
		    if ( mode == 1 ) draw_sprite_ex(bmp, subBmp2, dx, dy, DRAW_SPRITE_TRANS, flip);
		    if ( mode >= 2 ) draw_sprite_ex(bmp, subBmp2, dx, dy, DRAW_SPRITE_LIT, flip);
		    
            }
            else {
		 blit(sourceBitmap, subBmp, sx, sy, 0, 0, dw, dh); 
		    if ( mode <= 0 ) draw_sprite_ex(bmp, subBmp, dx, dy, DRAW_SPRITE_NORMAL, flip);
		    if ( mode == 1 ) draw_sprite_ex(bmp, subBmp, dx, dy, DRAW_SPRITE_TRANS, flip);
		    if ( mode >= 2 ) draw_sprite_ex(bmp, subBmp, dx, dy, DRAW_SPRITE_LIT, flip);		    
	    }
        }
    }
    
    //cleanup
    if(subBmp)
    {
        script_drawing_commands.ReleaseSubBitmap(subBmp);
    }
    //cleanup
    if(subBmp2)
    {
        script_drawing_commands.ReleaseSubBitmap(subBmp2);
    }
}

//! Polygon is Unfinished - Let's see if it works thus far, before I destroy meself. 

void do_polygonr(BITMAP *bmp, int *sdci, int xoffset, int yoffset)
{
    //sdci[1]=layer
    //sdci[2]=x
    //sdci[3]=y
	//scdi[4] = number of points
	//sdci[5]=vectors array
    //sdci[6]=color
    //sdci[7]=scale factor
    //sdci[8]=rotation anchor x
    //sdci[9]=rotation anchor y
    //sdci[10]=rotation angle
    //
    //sdci[12]=opacity
	
	
    
    int x1=sdci[2]/10000;
    int y1=sdci[3]/10000;
    int vertices=sdci[4]/10000;

	std::vector<long>* v_ptr = (std::vector<long>*)script_drawing_commands[i].GetPtr();
    
    if(!v_ptr)
    {
        al_trace("Polygon: Vector pointer is null! Internal error. \n");
        return;
    }
    
    std::vector<long> &v = *v_ptr;
    
    if(v.empty())
        return;
        
    long* points = &v[0];
	//Vector to hold vertices.
	
    if(sdci[7]==0)  //scale
    {
        return;
    }
    
    //int num_vertices = vertices*2;
    //int points[num_vertices];
    //! I believe that c++ allows expressing the array size declaration with an equation. 
    //! Is that correct?
    
    //getArray is at ffscript.cpp line 687
    //Using ZScript to <client> helper from line 760
    //getArray(scdi[4],points);
    
    //for ( int q = 0; q <= num_vertices; q++ ) {
	//    points[q] = getArray(scdi[4]);
    //}
    
    //Copy the contents of the array passed by scdi[4] to the local array points[].
    //! Is that the proper way to handle this?
    
    //int y2=sdci[5]/10000;
    //scdi[5] will contain an array points[x], where x is the value of (scdi[4] * 2)
    //We need to forward a ZScript array, containing the vertices information, each point needing two 
    //index positions in an array, to this value.
    //! Is that possible?
    //! Will normal array copying work here? If so, we can do a for loop, and copy the array to a local array, 
    //! or possibly just use the original?
    
    //! x2 ansd y2 do not apply to a polygon of no predefined number of vertices. 
    //if(x1>x2)
    //{
     //   zc_swap(x1,x2);
    //}
    
    //if(y1>y2)
    //{
    //    zc_swap(y1,y2);
    //}

	int color=sdci[6]/10000;
    
    if(sdci[7] != 10000)
    {
        int w=x2-x1+1;
        int h=y2-y1+1;
        int w2=(w*sdci[7])/10000;
        int h2=(h*sdci[7])/10000;
        x1=x1-((w2-w)/2);
        x2=x2+((w2-w)/2);
        y1=y1-((h2-h)/2);
        y2=y2+((h2-h)/2);
    }
    
    
    
    if(sdci[12]/10000<=127) //translucent
    {
        drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    }
    
    if(sdci[11]/10000>128) //XOR
    {
        drawing_mode(DRAW_MODE_XOR, NULL, 0, 0);
    }
    
    
    if(sdci[10]==0) //no rotation
    {
	     polygon(bmp, vertices, points, color);
        //if(sdci[11]) //filled
	    //! Polygons in Allegro 4 are *always* filled. 
        //{
	//	
         //   rectfill(bmp, x1+xoffset, y1+yoffset, x2+xoffset, y2+yoffset, color);
        //}
        //else //outline
        //{
         //   rect(bmp, x1+xoffset, y1+yoffset, x2+xoffset, y2+yoffset, color);
        //}
    }
    else  //rotate
    {
        //int xy[16];
        int rx=sdci[8]/10000;
        int ry=sdci[9]/10000;
        fixed ra1=itofix(sdci[10]%10000)/10000;
        fixed ra2=itofix(sdci[10]/10000);
        fixed ra=ra1+ra2;
        ra = (ra/360)*256;
        
        fixed fcosa = fixcos(ra);
        fixed fsina = fixsin(ra);
        
	    //! We need new rotational maths. 
	    
	/*
        xy[ 0]=xoffset+rx + fixtoi((fcosa * (x1 - rx) - fsina * (y1 - ry)));     //x1
        xy[ 1]=yoffset+ry + fixtoi((fsina * (x1 - rx) + fcosa * (y1 - ry)));     //y1
        xy[ 2]=xoffset+rx + fixtoi((fcosa * (x2 - rx) - fsina * (y1 - ry)));     //x2
        xy[ 3]=yoffset+ry + fixtoi((fsina * (x2 - rx) + fcosa * (y1 - ry)));     //y1
        xy[ 4]=xoffset+rx + fixtoi((fcosa * (x2 - rx) - fsina * (y2 - ry)));     //x2
        xy[ 5]=yoffset+ry + fixtoi((fsina * (x2 - rx) + fcosa * (y2 - ry)));     //y2
        xy[ 6]=xoffset+rx + fixtoi((fcosa * (x1 - rx) - fsina * (y2 - ry)));     //x1
        xy[ 7]=yoffset+ry + fixtoi((fsina * (x1 - rx) + fcosa * (y2 - ry)));     //y2
        xy[ 8]=xoffset+rx + fixtoi((fcosa * (x1 - rx) - fsina * (y1 - ry + 1)));         //x1
        xy[ 9]=yoffset+ry + fixtoi((fsina * (x1 - rx) + fcosa * (y1 - ry + 1)));         //y1
        xy[10]=xoffset+rx + fixtoi((fcosa * (x2 - rx - 1) - fsina * (y1 - ry)));         //x2
        xy[11]=yoffset+ry + fixtoi((fsina * (x2 - rx - 1) + fcosa * (y1 - ry)));         //y1
        xy[12]=xoffset+rx + fixtoi((fcosa * (x2 - rx) - fsina * (y2 - ry - 1)));         //x2
        xy[13]=yoffset+ry + fixtoi((fsina * (x2 - rx) + fcosa * (y2 - ry - 1)));         //y2
        xy[14]=xoffset+rx + fixtoi((fcosa * (x1 - rx + 1) - fsina * (y2 - ry)));         //x1
        xy[15]=yoffset+ry + fixtoi((fsina * (x1 - rx + 1) + fcosa * (y2 - ry)));         //y2
	
	*/
        
        if(sdci[11]) //filled
        {
            polygon(bmp, vertices, points, color);
		//We're already using Polygon for rectr, if filled. 
        }
	
	/*
	
        //else //outline
        //{
         //   line(bmp, xy[0], xy[1], xy[10], xy[11], color);
          //  line(bmp, xy[2], xy[3], xy[12], xy[13], color);
           // line(bmp, xy[4], xy[5], xy[14], xy[15], color);
            //line(bmp, xy[6], xy[7], xy[ 8], xy[ 9], color);
        //}
	
	
	*/
	//! We could do this with polygons that have no size limit, but it would be far more complicated.
    }
    
    drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
}


void do_pixelarrayr(BITMAP *bmp, int icommand, int *sdci, int xoffset, int yoffset)
{
	//sdci[1]=layer
	//sdci[2]=count
	//sdci[3]=x[]
	//sdci[4]=y[]
	//sdci[5]=colors[]

	long* p = (long*)script_drawing_commands[icommand].GetPtr();
	if(!p)
	{
		al_trace("do_pixelarrayr: pointer is null! Internal error. \n");
		return;
	}

	int count = sdci[2]/10000;
	long* px = p;
	long* py = p + count;
	long* pc = p + count * 2;

	for(int i(0); i != count; ++i)
	{
		putpixel(bmp,
			xoffset + px[i] / 10000,
			yoffset + py[i] / 10000,
			pc[i] / 10000);
	}

	script_drawing_commands.DeallocateDrawBuffer(p);
}


void do_tilearrayr(BITMAP *bmp, int icommand, int *sdci, int xoffset, int yoffset)
{
	//sdci[1]=layer
	//sdci[2]=count
	//sdci[3]=tile[]
	//sdci[4]=x[]
	//sdci[5]=y[]
	//sdci[6]=colors[]

	long* p = (long*)script_drawing_commands[icommand].GetPtr();
	if(!p)
	{
		al_trace("do_tilearrayr: pointer is null! Internal error. \n");
		return;
	}

	int count = sdci[2] / 10000;
	long* ptiles = p;
	long* px = p + count;
	long* py = p + count * 2;
	long* pc = p + count * 3;

	for(int i(0); i != count; ++i)
	{
		int x = px[i] / 10000;
		int y = py[i] / 10000;

		overtile16(bmp,
			ptiles[i] / 10000,
			xoffset + x,
			yoffset + y,
			pc[i] / 10000,
			0 //flip
		);
	}

	script_drawing_commands.DeallocateDrawBuffer(p);
}


void do_comboarrayr(BITMAP *bmp, int icommand, int *sdci, int xoffset, int yoffset)
{
	//sdci[1]=layer
	//sdci[2]=count
	//sdci[3]=tile[]
	//sdci[4]=x[]
	//sdci[5]=y[]
	//sdci[6]=colors[]

	long* p = (long*)script_drawing_commands[icommand].GetPtr();
	if(!p)
	{
		al_trace("do_tilearrayr: pointer is null! Internal error. \n");
		return;
	}

	int count = sdci[2]/10000;
	long* pcombos = p;
	long* px = p + count;
	long* py = p + count * 2;
	long* pc = p + count * 3;

	for(int i(0); i != count; ++i)
	{
		int x = px[i] / 10000;
		int y = py[i] / 10000;

		overtile16(bmp,
			combo_tile(pcombos[i] / 10000, x, y),
			xoffset + x,
			yoffset + y,
			pc[i] / 10000,
			0 //flip
		);
	}

	script_drawing_commands.DeallocateDrawBuffer(p);
}




bool is_layer_transparent(const mapscr& m, int layer)
{
    layer = vbound(layer, 0, 5);
    return m.layeropacity[layer] == 128;
}

mapscr *getmapscreen(int map_index, int screen_index, int layer)   //returns NULL for invalid or non-existent layer
{
    mapscr *base_screen;
    int index = map_index*MAPSCRS+screen_index;
    
    if((unsigned int)layer > 6 || (unsigned int)index >= TheMaps.size())
        return NULL;
        
    if(layer != 0)
    {
        layer = layer - 1;
        
        base_screen=&(TheMaps[index]);
        
        if(base_screen->layermap[layer]==0)
            return NULL;
            
        index=(base_screen->layermap[layer]-1)*MAPSCRS+base_screen->layerscreen[layer];
        
        if((unsigned int)index >= TheMaps.size())   // Might as well make sure
            return NULL;
    }
    
    return &(TheMaps[index]);
}

void draw_mapscr(BITMAP *b, const mapscr& m, int x, int y, bool transparent)
{
    for(int i(0); i < 176; ++i)
    {
        const int x2 = ((i&15)<<4) + x;
        const int y2 = (i&0xF0) + y;
        
        const newcombo & c = combobuf[ m.data[i] ];
        const int tile = combo_tile(c, x2, y2);
        
        if(transparent)
            overtiletranslucent16(b, tile, x2, y2, m.cset[i], c.flip, 128);
        else
            overtile16(b, tile, x2, y2, m.cset[i], c.flip);
    }
}
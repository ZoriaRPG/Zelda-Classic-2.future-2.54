void do_drawbitmapexr(BITMAP *bmp, int *sdci, int xoffset, int yoffset)
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
	//sdci[11]=rotation
	//scdi[12] = effect
	//sdci[13]=mask

	int bitmapIndex = sdci[2]/10000;
	int sx = sdci[3]/10000;
	int sy = sdci[4]/10000;
	int sw = sdci[5]/10000;
	int sh = sdci[6]/10000;
	int dx = sdci[7]/10000;
	int dy = sdci[8]/10000;
	int dw = sdci[9]/10000;
	int dh = sdci[10]/10000;
	float rot = scdi[11]/10000;
	int mode = sdci[11]/10000;
	bool masked = (sdci[12] != 0);

	//bugfix
	sx = vbound(sx, 0, 512);
	sy = vbound(sy, 0, 512);
	sw = vbound(sw, 0, 512 - sx); //keep the w/h within range as well
	sh = vbound(sh, 0, 512 - sy);


	if(sx >= ZScriptDrawingRenderTarget::BitmapWidth || sy >= ZScriptDrawingRenderTarget::BitmapHeight)
	return;

	bool stretched = (sw != dw || sh != dh);

	BITMAP *sourceBitmap = zscriptDrawingRenderTarget->GetBitmapPtr(bitmapIndex);
    
	if(!sourceBitmap)
	{
		Z_message("Warning: Screen->DrawBitmap(%d) contains invalid data or is not initialized.\n", bitmapIndex);
		Z_message("[Note* Deferred drawing or layering order possibly not set right.]\n");
		return;
	}
    
	BITMAP* subBmp = 0;
    
	if(mode != 0)
	{
		subBmp = script_drawing_commands.AquireSubBitmap(dw, dh);
        
		if(!subBmp)
		{
		}
	}
    
    
	dx = dx + xoffset;
	dy = dy + yoffset;
    
	if(stretched) {
		if(masked) {	
			if ( rot == 0 ) { //if rotated
				switch(mode) {
					case 1:
					//transparent
					masked_stretch_blit(sourceBitmap, subBmp, sx, sy, sw, sh, 0, 0, dw, dh);
					draw_trans_sprite(bmp, subBmp, dx, dy);
					break
					
					
					case 2: 
						//pivot?
					break;
					
					case 0: 
						//no effect
						masked_stretch_blit(sourceBitmap, bmp, sx, sy, sw, sh, dx, dy, dw, dh);
						break;
					
				}
			} //end if not rotated
			
			if ( rot != 0 ) { //if rotated
				switch(mode){
					case 1: 
						//transparent
					break;
					
					case 2: 
						//pivot?
					break;
					
					case 0: 
						//no effect.
					masked_stretch_blit(sourceBitmap, subBmp, sx, sy, sw, sh, 0, 0, dw, dh);
					rotate_sprite(bmp, subBmp, dx, dy, degrees_to_fixed(rot));
					break;
				
				}
			}
		} //end if masked
		
		else //not masked {
			
			if(rot == 0) { //no rotaion
				
				switch(mode){
					
					case 1:
						//translucent
					stretch_blit(sourceBitmap, subBmp, sx, sy, sw, sh, 0, 0, dw, dh);
					draw_trans_sprite(bmp, subBmp, dx, dy);
					break;
					
					case 2: 
						//pivot?
					break;
					
					case 0: 
						//no effect
						stretch_blit(sourceBitmap, bmp, sx, sy, sw, sh, dx, dy, dw, dh);
					break
				}
			} //end if not rotated
			
			if ( rot != 0 ) { //if rotated
				
				switch(mode){
					
					case 1: 
						//translucent
					break;
					
					case 2: 
						//pivot?
					break
					
					case 0: 
						//no effect
					stretch_blit(sourceBitmap, subBmp, sx, sy, sw, sh, 0, 0, dw, dh);
					rotate_sprite(bmp, subBmp, dx, dy, degrees_to_fixed(mode));
					break;
				}
			} //end if rotated
		} //end if stretched, but not masked
		
	else { //not stretched
		
		if(masked) { //if masked, but not stretched
			
			if ( rot == 0 ) { //no rotation
				switch(mode){
					
					case 1: 
						//translucent
					masked_blit(sourceBitmap, subBmp, sx, sy, 0, 0, dw, dh);
					draw_trans_sprite(bmp, subBmp, dx, dy);
					break;
					
					case 2: 
						//pivot?
					break;
					
					case 0: 
						//no effect
						masked_blit(sourceBitmap, bmp, sx, sy, dx, dy, dw, dh);
					break;
				}
			} //end no rotation
			
			if ( rot != 0 ) { //rotated, masked
				switch(mode){
					
					case 1: 
						//translucent
					break;
					
					case 2: 
						//pivot?
					break;
					
					case 0: 
						//no effects
					masked_blit(sourceBitmap, subBmp, sx, sy, 0, 0, dw, dh);
					rotate_sprite(bmp, subBmp, dx, dy, degrees_to_fixed(mode));  
					break;
				}
			} //end rtated, masked
		} //end if masked

		else { //not masked, and not stretched
			
			if(rot == 0) { //not rotated
				switch(mode){
					
					case 1: 
						//translucent
					blit(sourceBitmap, subBmp, sx, sy, 0, 0, dw, dh);   
					draw_trans_sprite(bmp, subBmp, dx, dy);
					break;
					
					case 2: 
						//pivot?
					break;
					
					case 0: // no effects
					blit(sourceBitmap, bmp, sx, sy, dx, dy, dw, dh);
					break;
				}
			} //end if not rotated
			
			if ( rot != 0 ) { //rotated
				switch(mode){
					
					case 1: 
						//translucent
					break;
					
					case 2: 
						//pivot;
					break;
					
					case 0:
						//no effects
					blit(sourceBitmap, subBmp, sx, sy, 0, 0, dw, dh);
					rotate_sprite(bmp, subBmp, dx, dy, degrees_to_fixed(mode));
					break;
				}
			} //end if rotated
		} //end if not masked
	} //end if not stretched
    
	//cleanup
	if(subBmp) {
		script_drawing_commands.ReleaseSubBitmap(subBmp); //purge the temporary bitmap.
	}
}
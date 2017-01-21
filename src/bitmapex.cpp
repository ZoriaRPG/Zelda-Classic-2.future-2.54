void do_transdrawbitmapr(BITMAP *bmp, int *sdci, int xoffset, int yoffset)
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
	//sdci[12]=mask

	int bitmapIndex = sdci[2]/10000;
	int sx = sdci[3]/10000;
	int sy = sdci[4]/10000;
	int sw = sdci[5]/10000;
	int sh = sdci[6]/10000;
	int dx = sdci[7]/10000;
	int dy = sdci[8]/10000;
	int dw = sdci[9]/10000;
	int dh = sdci[10]/10000;
	float mode = sdci[11]/10000;
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
    
	if(stretched)
	{
		if(masked)
		{
			
			if(mode != 0)
			{	
				if ( mode == 1 ) { //translucent
					masked_stretch_blit(sourceBitmap, subBmp, sx, sy, sw, sh, 0, 0, dw, dh);
					//rotate_sprite_trans(bmp, subBmp, dx, dy, degrees_to_fixed(mode));
					draw_trans_sprite(bmp, subBmp, dx, dy);
					//draw_sprite_ex(bmp, subBmp, dx, dy, DRAW_SPRITE_TRANS, 0);
			
			
				}
				else { 
					masked_stretch_blit(sourceBitmap, subBmp, sx, sy, sw, sh, 0, 0, dw, dh);
					rotate_sprite(bmp, subBmp, dx, dy, degrees_to_fixed(mode));
					//rotate_sprite(bmp, subBmp, dx, dy, degrees_to_fixed(mode));
					//
			
				}
			}
			else
				masked_stretch_blit(sourceBitmap, bmp, sx, sy, sw, sh, dx, dy, dw, dh);
		}
		else
		{
			if(mode != 0)
			{
				if ( mode == 1 ) { //translucent
					stretch_blit(sourceBitmap, subBmp, sx, sy, sw, sh, 0, 0, dw, dh);
					draw_trans_sprite(bmp, subBmp, dx, dy);
				}
				else {
					stretch_blit(sourceBitmap, subBmp, sx, sy, sw, sh, 0, 0, dw, dh);
					rotate_sprite(bmp, subBmp, dx, dy, degrees_to_fixed(mode));
				}
			}
			else
				stretch_blit(sourceBitmap, bmp, sx, sy, sw, sh, dx, dy, dw, dh);
		}
	}
	else
	{
		if(masked)
		{
			if(mode != 0)
			{
				if ( mode == 1 ) {//translucent
					masked_blit(sourceBitmap, subBmp, sx, sy, 0, 0, dw, dh);
					//rotate_sprite(bmp, subBmp, dx, dy, degrees_to_fixed(mode));
		    
					//masked_stretch_blit(sourceBitmap, subBmp, sx, sy, sw, sh, 0, 0, dw, dh);
					//rotate_sprite_trans(bmp, subBmp, dx, dy, degrees_to_fixed(mode));
					draw_trans_sprite(bmp, subBmp, dx, dy);
				}
			else {
				masked_blit(sourceBitmap, subBmp, sx, sy, 0, 0, dw, dh);
				rotate_sprite(bmp, subBmp, dx, dy, degrees_to_fixed(mode));  
			}
		}
		else
			masked_blit(sourceBitmap, bmp, sx, sy, dx, dy, dw, dh);
		}
		else
		{
			if(mode != 0)
			{
				if ( mode == 1 ) { //translucent
					blit(sourceBitmap, subBmp, sx, sy, 0, 0, dw, dh);   
					draw_trans_sprite(bmp, subBmp, dx, dy);
				}
				else {
					blit(sourceBitmap, subBmp, sx, sy, 0, 0, dw, dh);
					rotate_sprite(bmp, subBmp, dx, dy, degrees_to_fixed(mode));
				}
			}
			else
				blit(sourceBitmap, bmp, sx, sy, dx, dy, dw, dh);
		}
	}
    
	//cleanup
	if(subBmp)
	{
		script_drawing_commands.ReleaseSubBitmap(subBmp);
	}
}
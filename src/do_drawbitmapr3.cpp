
void do_drawbitmapr(BITMAP *bmp, int *sdci, int xoffset, int yoffset)
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
    float rot = sdci[11]/10000;
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
            if(rot <= 360 && rot > 0)
            {
                masked_stretch_blit(sourceBitmap, subBmp, sx, sy, sw, sh, 0, 0, dw, dh);
                rotate_sprite(bmp, subBmp, dx, dy, degrees_to_fixed(rot));
            }
	    else if( rot > 360 && rot < 721 )
            {
                masked_stretch_blit(sourceBitmap, subBmp, sx, sy, sw, sh, 0, 0, dw, dh);
               rotate_sprite_trans(bmp, subBmp, dx, dy, degrees_to_fixed(rot));
            }
	    else if(rot >= 721)
            {
                masked_stretch_blit(sourceBitmap, subBmp, sx, sy, sw, sh, 0, 0, dw, dh);
                rotate_sprite_trans(bmp, subBmp, dx, dy, 0);
            }
            else
                masked_stretch_blit(sourceBitmap, bmp, sx, sy, sw, sh, dx, dy, dw, dh);
        }
        else
        {
            if(rot != 0)
            {
                stretch_blit(sourceBitmap, subBmp, sx, sy, sw, sh, 0, 0, dw, dh);
                rotate_sprite(bmp, subBmp, dx, dy, degrees_to_fixed(rot));
            }
            else
                stretch_blit(sourceBitmap, bmp, sx, sy, sw, sh, dx, dy, dw, dh);
        }
    }
    else
    {
        if(masked)
        {
            if(rot <= 360 && rot > 0)
            {
                masked_blit(sourceBitmap, subBmp, sx, sy, 0, 0, dw, dh);
                rotate_sprite(bmp, subBmp, dx, dy, degrees_to_fixed(rot));
            }
	    else if(rot > 360 && rot < 721)
            {
                masked_blit(sourceBitmap, subBmp, sx, sy, 0, 0, dw, dh);
                rotate_sprite_trans(bmp, subBmp, dx, dy, degrees_to_fixed(rot));
            }
	    else if(rot >= 721)
            {
                masked_blit(sourceBitmap, subBmp, sx, sy, 0, 0, dw, dh);
                rotate_sprite_trans(bmp, subBmp, dx, dy, 0);
            }
            else
                masked_blit(sourceBitmap, bmp, sx, sy, dx, dy, dw, dh);
        }
        else
        {
            if(rot != 0)
            {
                blit(sourceBitmap, subBmp, sx, sy, 0, 0, dw, dh);
                rotate_sprite(bmp, subBmp, dx, dy, degrees_to_fixed(rot));
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


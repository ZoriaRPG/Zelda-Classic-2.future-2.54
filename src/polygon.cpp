void do_polygonr(BITMAP *bmp, int i, int *sdci, int xoffset, int yoffset){
	
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
	
	long* p = script_drawing_commands[i].GetPtr();
    
    if(!p)
    {
        al_trace("Polygon: Vector pointer is null! Internal error. \n");
        return;
    };
    long* points = &p[0];
    
    int x = sdci[2]/10000;
    int y = sdci[3]/10000;
    int numpoints = sdci[4]/10000;
    //5 is the array
    int colour = sdci[6]/10000;
    int scale = sdci[7]/10000;
    int rotx = sdci[8]/10000;
    int roty = sdci[9]/10000;
    int rangle = sdci[10]/10000;
    int opacity = sdci[11]/10000;
    
    /*
    int w = size[0]; //magic numerical constants... yuck.
    int h = size[1];
    int flip = (sdci[6]/10000)&3;
    int tile = sdci[7]/10000;
    int polytype = sdci[8]/10000;
    */
    
    polytype = vbound(polytype, 0, 14);
    
    if ( scale ) {
	    return;
    }
    
    if( opacity <= 127 ) {
	    //translucent
        drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
    }
    
    else  drawing_mode(DRAW_MODE_SOLID, NULL, 0, 0);
    
    if ( rangle == 0 )  { 
	    //No rotation
	polygon(bmp, numpoints, points, colour);    
    }
    else { 
	    return;
	    //Rotation goes here.
    }
}
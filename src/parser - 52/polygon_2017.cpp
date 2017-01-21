void do_polygonr(BITMAP *bmp, int *sdci, int xoffset, int yoffset)
{
    //sdci[1]=layer
	//x
	//y
    //sdci[2]=vertices //size of points[] / 2
    //sdci[3]=*points[]
    //sdci[4]=colour
	//sdci[5]=opacity
    
    int vertices = sdci[2]/10000;
    int colour = sdci[3]/10000;
	//[4] is the array
	int opacity = sdci[5]/10000;
	std::vector<long> *v = script_drawing_commands.GetVector();
	long* points = &v->at(0);
	
	ZScriptArray& a = getArray(sdci[3]/10000);
	ArrayH::getValues(script_drawing_commands[j][2] / 10000, pos, 12);
    
        
}

void do_polygonr(BITMAP *bmp, int *sdci, int xoffset, int yoffset)
{
	//sdci[1]=layer
	//sdci[2]=vertices //size of points[] / 2
	//sdci[3]=*points[]
	//sdci[4]=colour
	//sdci[5]=opacity
    
	int vertices = sdci[2]/10000;
	int colour = sdci[3]/10000;
	long arrayptr = scdi[4] / 10000;
	int opacity = sdci[5]/10000;
	int size = ArrayH::getSize(arrayptr);
	int points[size];
	ArrayH::getValues(arrayptr, points, size);
	
	if(sdci[5]/10000<=127) //translucent
	{
		drawing_mode(DRAW_MODE_TRANS, NULL, 0, 0);
	}
	polygon(bmp, vertices, points, color);
}


void do_polygonr(BITMAP *bmp, int icommand, int *sdci, int xoffset, int yoffset)
{
	//sdci[1]=layer
	//sdci[2]=vertices //size of points[] / 2
	//sdci[3]=*points[]
	//sdci[4]=colour
	//sdci[5]=opacity
	int vertices = sdci[2]/10000;
	int colour = sdci[3]/10000;
	//[4] is the array
	int opacity = sdci[5]/10000;

	long* points = (long*)ArrayH::getArray(sdci[3]/10000);
	if(!points)
	{
		al_trace("Polygon(): pointer is null! Internal error. \n");
		return;
	}

	int vertices = sdci[2]/10000;

	ArrayH::getValues(getArray(sdci[3]/10000) / 10000, points, (vertices*2));
	
	polygon(BITMAP *bmp, int vertices, const int *points, int color);
}


void do_polygonr(BITMAP *bmp, int icommand, int *sdci, int xoffset, int yoffset)
{
	//sdci[1]=layer
	//sdci[2]=vertices //size of points[] / 2
	//sdci[3]=*points[]
	//sdci[4]=colour
	//sdci[5]=opacity
	int vertices = sdci[2]/10000;
	int colour = sdci[3]/10000;
	//[4] is the array
	int opacity = sdci[5]/10000;

	long* points = (long*)ArrayH::getArray(sdci[3]/10000);
	if(!points)
	{
		al_trace("Polygon(): pointer is null! Internal error. \n");
		return;
	}

	int vertices = sdci[2]/10000;

	ArrayH::getValues(getArray(sdci[3]/10000) / 10000, points, (vertices*2));
	
	polygon(BITMAP *bmp, int vertices, const int *points, int color);
}

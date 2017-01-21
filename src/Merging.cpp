//script drawing.cpp

void do_polygonr(){}

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
/*
case POLYGONR:
		{
			do_polygonr(bmp, sdci, xoffset, yoffset);
		}
		break;
*/

		case PIXELARRAYR:
		{
			do_pixelarrayr(bmp, i, sdci, xoffset, yoffset);
		}
		break;

		case TILEARRAYR:
		{
			do_tilearrayr(bmp, i, sdci, xoffset, yoffset);
		}
		break;

		case COMBOARRAYR:
		{
			do_comboarrayr(bmp, i, sdci, xoffset, yoffset);
		}
		break;

//global symbols.cpp
		
		
#define ARGS_3(t, arg1, arg2, arg3) { t, arg1, arg2, arg3, -1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }
#define ARGS_4(t, arg1, arg2, arg3, arg4) { t, arg1, arg2, arg3, arg4, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }
#define ARGS_5(t, arg1, arg2, arg3, arg4, arg5) { t, arg1, arg2, arg3, arg4, arg5, -1, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }
#define ARGS_6(t, arg1, arg2, arg3, arg4, arg5, arg6) { t, arg1, arg2, arg3, arg4, arg5, arg6, -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }
#define ARGS_8(t, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) { t, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }
#define ARGS_12(t, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12) { t, arg1, arg2, arg3, arg4, arg5,
		
		
{ "DrawPixelArray",    typeVOID, FUNCTION, 0, 1, ARGS_5(S,F,F,F,F,F) },
	{ "DrawTileArray",     typeVOID, FUNCTION, 0, 1, ARGS_6(S,F,F,F,F,F,F) },
	{ "DrawComboArray",    typeVOID, FUNCTION, 0, 1, ARGS_6(S,F,F,F,F,F,F) },
	{ "CreateBitmap",      typeVOID, FUNCTION, 0, 1, ARGS_3(S,F,F,F) },
	{ "SetRenderSource",   typeVOID, FUNCTION, 0, 1, ARGS_5(S,F,F,F,F,F) },
 
  
	//void DrawPolygon(screen, float, float, float, float, float, float, float)
	{
		int id = memberids["Polygon"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new ODrawPolygonRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(6, EXP2);

		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));

		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	//void DrawPixelArray(screen, float, float, float)
	{
		int id = memberids["DrawPixelArray"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new ODrawPixelArrayRegister();
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));

		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));

		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	//void DrawTileArray(screen, float, float, float, float, float)
	{
		int id = memberids["DrawTileArray"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new ODrawTileArrayRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(6, EXP2);

		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));

		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	//void DrawComboArray(screen, float, float, float, float, float)
	{
		int id = memberids["DrawComboArray"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new ODrawComboArrayRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(6, EXP2);

		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));

		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	//void CreateBitmap(bitmap, float, float, float)
	{
		int id = memberids["CreateBitmap"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OCreateBitmapRegister();
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OPopRegister(new VarArgument(EXP2)));

		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));

		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	//void SetRenderSource(bitmap,x,y,w,h)
	{
		int id = memberids["SetRenderSource"];
		int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OSetRenderSourceRegister();
		first->setLabel(label);
		code.push_back(first);
		POP_ARGS(5, EXP2);
		//pop pointer, and ignore it
		code.push_back(new OPopRegister(new VarArgument(NUL)));

		code.push_back(new OPopRegister(new VarArgument(EXP2)));
		code.push_back(new OGotoRegister(new VarArgument(EXP2)));
		rval[label]=code;
	}
	
	
	
//bytecode.cpp
	
	
string ODrawPolygonRegister::toString()
{
	return "DRAWPOLYGON";
}

string ODrawPixelArrayRegister::toString()
{
	return "DRAWPIXELARRAY";
}

string ODrawTileArrayRegister::toString()
{
	return "DRAWTILEARRAY";
}

string ODrawComboArrayRegister::toString()
{
	return "DRAWCOMBOARRAY";
}

string OCreateBitmapRegister::toString()
{
    return "CREATEBITMAP";
}

string OSetRenderSourceRegister::toString()
{
	return "SETRENDERSOURCE";
}


//byecode.h


class ODrawPolygonRegister : public Opcode
{
public:
	string toString();
	Opcode *clone()
	{
		return new ODrawPolygonRegister();
	}
};

class ODrawPixelArrayRegister : public Opcode
{
public:
	string toString();
	Opcode *clone()
	{
		return new ODrawPixelArrayRegister();
	}
};

class ODrawTileArrayRegister : public Opcode
{
public:
	string toString();
	Opcode *clone()
	{
		return new ODrawTileArrayRegister();
	}
};

class ODrawComboArrayRegister : public Opcode
{
public:
	string toString();
	Opcode *clone()
	{
		return new ODrawComboArrayRegister();
	}
};

class OCreateBitmapRegister : public Opcode
{
public:
	string toString();
	Opcode *clone()
	{
		return new OCreateBitmapRegister();
	}
};



class OSetRenderSourceRegister : public Opcode
{
public:
	string toString();
	Opcode *clone()
	{
		return new OSetRenderSourceRegister();
	}
};

//ffasm.cpp

{ "SETRENDERSOURCE",     0,   0,   0,   0},
	{ "CREATEBITMAP",        0,   0,   0,   0},
	{ "POLYGONR",            0,   0,   0,   0},
	{ "PIXELARRAYR",         0,   0,   0,   0},
	{ "TILEARRAYR",          0,   0,   0,   0},
	{ "COMBOARRAYR",         0,   0,   0,   0},

//ffscript.cpp

	
	case POLYGONR:
		{
			set_drawing_command_args(j, 6);
			int count = script_drawing_commands[j][2] / 10000; //todo: errcheck

			long* ptr = (long*)script_drawing_commands.AllocateDrawBuffer(3 * count * sizeof(long));
			long* p = ptr;

			ArrayH::getValues(script_drawing_commands[j][3] / 10000, p, count); p += count;
			ArrayH::getValues(script_drawing_commands[j][4] / 10000, p, count); p += count;
			ArrayH::getValues(script_drawing_commands[j][5] / 10000, p, count);
			
			ZScriptDrawingRenderTarget::SourceParamInfo& si = zscriptDrawingRenderTarget->GetCurrentRenderSourceInfo();
			if(si.i)
			{
				script_drawing_commands[j][10] = si.i;
				script_drawing_commands[j][11] = si.x;
				script_drawing_commands[j][12] = si.y;
				script_drawing_commands[j][13] = si.w;
				script_drawing_commands[j][14] = si.h;
			}

			script_drawing_commands[j].SetPtr(ptr);
		}
		break;

	case PIXELARRAYR:
		{
			set_drawing_command_args(j, 5);
			int count = script_drawing_commands[j][2] / 10000; //todo: errcheck

			long* ptr = (long*)script_drawing_commands.AllocateDrawBuffer(3 * count * sizeof(long));
			long* p = ptr;

			ArrayH::getValues(script_drawing_commands[j][3] / 10000, p, count); p += count;
			ArrayH::getValues(script_drawing_commands[j][4] / 10000, p, count); p += count;
			ArrayH::getValues(script_drawing_commands[j][5] / 10000, p, count);

			script_drawing_commands[j].SetPtr(ptr);
		}
		break;

	case TILEARRAYR:
		{
			set_drawing_command_args(j, 6);
			int count = script_drawing_commands[j][2] / 10000; //todo: errcheck

			long* ptr = (long*)script_drawing_commands.AllocateDrawBuffer(3 * count * sizeof(long));
			long* p = ptr;

			ArrayH::getValues(script_drawing_commands[j][3] / 10000, p, count); p += count;
			ArrayH::getValues(script_drawing_commands[j][4] / 10000, p, count); p += count;
			ArrayH::getValues(script_drawing_commands[j][5] / 10000, p, count);

			script_drawing_commands[j].SetPtr(ptr);
		}
		break;

	case COMBOARRAYR:
		{
			set_drawing_command_args(j, 6);
			int count = script_drawing_commands[j][2] / 10000; //todo: errcheck

			long* ptr = (long*)script_drawing_commands.AllocateDrawBuffer(3 * count * sizeof(long));
			long* p = ptr;

			ArrayH::getValues(script_drawing_commands[j][3] / 10000, p, count); p += count;
			ArrayH::getValues(script_drawing_commands[j][4] / 10000, p, count); p += count;
			ArrayH::getValues(script_drawing_commands[j][5] / 10000, p, count);

			script_drawing_commands[j].SetPtr(ptr);
		}
		break;

	}
	
	
	///functions
	
	

//todo: Could probably use some error checking...
void do_createbitmap(bool)
{
	int target = int(SH::read_stack(ri->sp + 2) / 10000);
	int x = int(SH::read_stack(ri->sp + 1) / 10000);
	int y = int(SH::read_stack(ri->sp) / 10000);
	zscriptDrawingRenderTarget->CreateBitmap(target, x, y);
}

void do_set_rendersource(bool)
{
	int target = int(SH::read_stack(ri->sp + 4) / 10000);
	int x = int(SH::read_stack(ri->sp + 3) / 10000);
	int y = int(SH::read_stack(ri->sp + 2) / 10000);
	int w = int(SH::read_stack(ri->sp + 1) / 10000);
	int h = int(SH::read_stack(ri->sp) / 10000);
	zscriptDrawingRenderTarget->SetCurrentRenderSource(target, x, y, w, h);
}

///

case BITMAPEXR:
		case POLYGONR:
		case PIXELARRAYR:
		case TILEARRAYR:
		case COMBOARRAYR:
	
	
//ffscript.h
		
		SETRENDERSOURCE,      //0x00E9
	CREATEBITMAP,         //0x00EA
	POLYGONR,             //0x00EC
	PIXELARRAYR,          //0x00ED
	TILEARRAYR,           //0x00EE
	COMBOARRAYR,          //0x00EF
		
		


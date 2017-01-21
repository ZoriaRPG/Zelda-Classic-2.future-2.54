//Beta 24

//////////////
/// link.h ///
//////////////

void setTile(int state, int tile, int dir, int flip);
int getExtend(int state, int dir);
void setExtend(int state, int dir, int value);
    
    
////////////////
/// link.cpp ///
////////////////

//Set Link's tile
//Link->SetTile(state, tile, dir, flip)
void LinkClass::setTile(int state, int tile, int dir, int flip){
	setlinktile(tile, flip, getExtend(state,dir), state, dir);
}

//Link->Extend

void LinkClass::setExtend(int state, int dir, int value){
	switch(state){
		case 1: 
			walkspr[dir][spr_extend] = value;
			break;
		case 2: 
			floatspr[dir][spr_extend] = value;
			break;
		case 3: 
			swimspr[dir][spr_extend] = value;
			break;
		case 4: 
			divespr[dir][spr_extend] = value;
			break;
		case 5:
			slashspr[dir][spr_extend] = value;
			break;
		case 6:
			jumpspr[dir][spr_extend] = value;
			break;
		case 7: 
			chargespr[dir][spr_extend] = value;
			break;
		case 8:
			stabspr[dir][spr_extend] = value;
			break;
		case 9: 
			poundspr[dir][spr_extend] = value;
			break;
		case 10: 
			castingspr[spr_extend] = value;
			break;
		case 11: 
			holdspr[spr_landhold][spr_hold1][spr_extend] = value;
			break;
		case 12: 
			holdspr[spr_landhold][spr_hold2][spr_extend] = value;
			break;
		case 13: 
			holdspr[spr_waterhold][spr_hold1][spr_extend] = value;
			break;
		case 14: 
			holdspr[spr_waterhold][spr_hold2][spr_extend] = value;
		
		default: break;
	}
}

int LinkClass::getExtend(int state, int dir){
	switch(state){
		case 1: 
			return walkspr[dir][spr_extend];
		case 2: 
			return floatspr[dir][spr_extend];
		case 3: 
			return swimspr[dir][spr_extend];
		case 4: 
			return divespr[dir][spr_extend];		
		case 5: 
			return slashspr[dir][spr_extend];
		case 6:
			return jumpspr[dir][spr_extend];
		case 7: 
			return chargespr[dir][spr_extend];
		case 8:
			return stabspr[dir][spr_extend];
		case 9: 
			return poundspr[dir][spr_extend];
		case 10: 
			return castingspr[spr_extend];
		case 11: 
			return holdspr[spr_landhold][spr_hold1][spr_extend];
		case 12: 
			return holdspr[spr_landhold][spr_hold2][spr_extend];
		case 13: 
			return holdspr[spr_waterhold][spr_hold1][spr_extend];
		case 14: 
			return holdspr[spr_waterhold][spr_hold2][spr_extend];
		default: return -1;
	}
}


/////////////////
/// ffasm.cpp ///
/////////////////

{ "SETLINKTILE", 0,   0,   0,   0},
{ "SETLINKEXTEND", 0,   0,   0,   0},
{ "GETLINKEXTEND", 2,   0,   0,   0},


//////////////////
/// ffscript.h ///
//////////////////

SETLINKTILE, //0x00F1
SETLINKEXTEND, //0x00F2
GETLINKEXTEND, //0x00F3
     

////////////////////
/// ffscript.cpp ///
////////////////////
    
    case SETLINKTILE:
		Z_message("Trying to set Link's tile.\n");
		set_link_tile(false);
		break;
    
    case SETLINKEXTEND:
		Z_message("Trying to set Link->SetExtend().\n");
		set_link_extend(false);
		break;
    
    case GETLINKEXTEND:
		Z_message("Trying to get Link->GetExtend().\n");
		get_link_extend(true);
		break;
	
	
	
void set_link_tile(bool v)
{
    int state   = SH::read_stack(ri->sp + 3) / 10000;
    int tile = SH::read_stack(ri->sp + 2) / 10000;
    int dir   = SH::read_stack(ri->sp + 1) / 10000;
    int flip   = SH::read_stack(ri->sp + 0) / 10000;
    Link.setTile(vbound(state,1,14),vbound(tile,0,65519),vbound(dir,0,16),vbound(flip,0,16));
}

void set_link_extend(bool v)
{
    int state   = SH::read_stack(ri->sp + 2) / 10000;
    int extend = SH::read_stack(ri->sp + 1) / 10000;
    int dir   = SH::read_stack(ri->sp + 0) / 10000;
    Link.setExtend(vbound(state,1,14),vbound(dir,0,16),vbound(extend,0,16));
}

void get_link_extend(bool v)
{
    int state   = SH::read_stack(ri->sp + 1) / 10000;
    int dir   = SH::read_stack(ri->sp + 0) / 10000;
    int extend = (int)Link.getExtend(state, dir);
    set_register(sarg1, extend*10000);
}

//////////////////
/// Bytecode.h ///
//////////////////

#define LINKEXTEND 392
#define SETLINKEXTEND 393
#define GETLINKEXTEND 394


class OSetLinkTile : public Opcode
{
public:
    string toString();
    Opcode *clone()
    {
        return new OSetLinkTile();
    }
};

class OSetLinkExtend : public Opcode
{
public:
    string toString();
    Opcode *clone()
    {
        return new OSetLinkExtend();
    }
};

class OGetLinkExtend : public BinaryOpcode
{
public:
    OGetLinkExtend(Argument *A, Argument *B) : BinaryOpcode(A,B) {}
    string toString();
    Opcode *clone()
    {
        return new OGetLinkExtend(a->clone(), b->clone());
    }
};

////////////////////
/// Bytecode.cpp ///
////////////////////

string OSetLinkTile::toString()
{
    return "SETLINKTILE";
}

string OSetLinkExtend::toString()
{
    return "SETLINKEXTEND";
}
string OGetLinkExtend::toString()
{
    return "GETLINKEXTEND " + getFirstArgument()->toString() + "," + getSecondArgument()->toString();
}

/////////////////////////
/// GLobalSymbols.cpp ///
/////////////////////////

{ "SetTile",                ScriptParser::TYPE_VOID,          FUNCTION,     0,                    1,      {  ScriptParser::TYPE_LINK,          ScriptParser::TYPE_FLOAT,         ScriptParser::TYPE_FLOAT,    ScriptParser::TYPE_FLOAT,   ScriptParser::TYPE_FLOAT,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1                           } },
{ "SetLinkExtend",                ScriptParser::TYPE_VOID,          FUNCTION,     0,                    1,      {  ScriptParser::TYPE_LINK,          ScriptParser::TYPE_FLOAT,         ScriptParser::TYPE_FLOAT,    ScriptParser::TYPE_FLOAT,   -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1                           } },
{ "GetLinkExtend",                ScriptParser::TYPE_FLOAT,          FUNCTION,     0,                    1,      {  ScriptParser::TYPE_LINK,          ScriptParser::TYPE_FLOAT,         ScriptParser::TYPE_FLOAT,    -1,   -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1,                           -1                           } },
   
//void SetLinkTile(link, int,int,int,int)
    {
        int id = memberids["SetTile"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        Opcode *first = new OSetLinkTile();
        first->setLabel(label);
        code.push_back(first);
        code.push_back(new OPopRegister(new VarArgument(EXP2))); //!ZoriaRPG this can't be right
        code.push_back(new OPopRegister(new VarArgument(EXP2))); //only one expr accumulator?
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OPopRegister(new VarArgument(EXP2))); 
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label]=code;
    }
    
    //void OSetLinkExtend
    {
        int id = memberids["SetLinkExtend"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        Opcode *first = new OSetLinkExtend();
        first->setLabel(label);
        code.push_back(first);
        code.push_back(new OPopRegister(new VarArgument(EXP2))); //!ZoriaRPG this can't be right
        code.push_back(new OPopRegister(new VarArgument(EXP2))); //only one expr accumulator, and number two?
        code.push_back(new OPopRegister(new VarArgument(EXP2))); //is this extraneous?
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label]=code;
    }
    //void GetLinkExtend(link, int, int)
    {
        int id = memberids["GetLinkExtend"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        //pop off the params
        Opcode *first = new OPopRegister(new VarArgument(EXP1));
        first->setLabel(label);
        code.push_back(first);
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        code.push_back(new OGetLinkExtend(new VarArgument(EXP2), new VarArgument(EXP1)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label] = code;
    }
    
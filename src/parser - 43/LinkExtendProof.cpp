//Setter Link->SetExtend(int sprite, int dir, int value)

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

void set_link_extend(bool v)
{
    int state   = SH::read_stack(ri->sp + 2) / 10000;
    int extend = SH::read_stack(ri->sp + 1) / 10000;
    int dir   = SH::read_stack(ri->sp) / 10000;
    Link.setExtend(vbound(state,1,14),vbound(dir,0,16),vbound(extend,0,16));
}


    
string OSetLinkExtend::toString()
{
    return "SETLINKEXTEND";
}

{ "SETLINKEXTEND",            0,   0,   0,   0},
    
	
case SETLINKEXTEND:
	set_link_extend(false);
	break;

string OSetLinkExtend::toString()
{
    return "SETLINKEXTEND";
}



    //void SetLinkExtend(link, int,int,int,int)
    {
        int id = memberids["SetLinkExtend"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        Opcode *first = new OSetLinkExtend();
        first->setLabel(label);
        code.push_back(first);
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OPopRegister(new VarArgument(EXP2))); //is this extraneous?
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label]=code;
    }

class OSetLinkExtend : public Opcode
{
public:
    string toString();
    Opcode *clone()
    {
        return new OSetLinkExtend();
    }
};


//Getter Fuction: Link->GetExtend(int sprite, int dir)

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

void get_link_extend(bool v)
{
    int state   = SH::read_stack(ri->sp + 1) / 10000;
    int dir   = SH::read_stack(ri->sp) / 10000;
    int extend = Link.getExtend(state, dir);
    set_register(sarg1, extend*10000);
}

string OGetLinkExtend::toString()
{
    return "GETLINKEXTEND " + getArgument()->toString();
}

{ "GETLINKEXTEND",     1,   0,   0,   0},
    
case GETLINKEXTEND:
	get_link_extend(true);
	break;

string OGetLinkExtend::toString()
{
    return "GETLINKEXTEND " + getArgument()->toString();
}

  //int GetLinkExtend(link, int, int)
    {
        int id = memberids["GetLinkExtend"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        Opcode *first = new OPopRegister(new VarArgument(EXP1));
        first->setLabel(label);
	code.push_back(first);
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OPopRegister(new VarArgument(EXP2))); //Is this extraneous?
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        code.push_back(new OGetLinkExtend(new VarArgument(EXP1)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label]=code;
    }

class OGetLinkExtend : public UnaryOpcode
{
public:
    OGetLinkExtend(Argument *A) : UnaryOpcode(A) {}
    string toString();
    Opcode *clone()
    {
        return new OGetLinkExtend(a->clone());
    }
};
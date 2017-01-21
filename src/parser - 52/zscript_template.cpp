
    //lweapon CreateLWeaponDX(screen, int type, int itemid)
    {
        int id = memberids["CreateLWeaponDx"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        //pop off the params
        Opcode *first = new OPopRegister(new VarArgument(INDEX2));
        first->setLabel(label);
        code.push_back(first);
        code.push_back(new OPopRegister(new VarArgument(INDEX)));
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(CREATELWPNDX)));

        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label] = code;
    }
     
    //ZScriptFunction("SetSomething", 3, SETSOMETHING, false);
    //ZScriptFunction("GetSomething", 3, GETSOMETHING, true);
void ZScriptFunction(const char * const str, int args, short instruction, bool do_return){
	int id = memberids[str];
	int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        //pop off the params
        Opcode *first = new OPopRegister(new VarArgument(INDEX2));
	first->setLabel(label);
        code.push_back(first);
        code.push_back(new OPopRegister(new VarArgument(INDEX)));
	 //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
	if ( do_return ) code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(instruction)));
	else code.push_back(new OSetRegister(new VarArgument(instruction), new VarArgument(INDEX2)));
	for ( int q = 1; q <= args; q++ ) code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label] = code;
}
	
//int SizeOfArray(int (ptr)
    {
        id = memberids["SizeOfArray"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        Opcode *first = new OPopRegister(new VarArgument(EXP1));
        first->setLabel(label);
        code.push_back(first);
        code.push_back(new OArraySize(new VarArgument(EXP1)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label]=code;
    } //int SizeOfArrayBool(bool *ptr)
    
    
    void ZScriptFunctioReturn(int args, int label, int accum1, int accum2, int opcode, const char * const str){
	    int id = memberids[str];
	    int label = lt.functionToLabel(id);
		vector<Opcode *> code;
		Opcode *first = new OPopRegister(new VarArgument(accum1));
		first->setLabel(label);
		code.push_back(first);
		code.push_back(new opcode(new VarArgument(accum1)));
		POP_ARGS(args, accum2);
	        code.push_back(new OGotoRegister(new VarArgument(accum2)));
	        rval[label]=code;
	
	}
	void ZScriptFunctionNoReturn(int args, int label, int accum1, int accum2, int opcode, const char * const str){
		
		
		
		
		 //int GetPointer(ffc, ffc)
    {
        int id = memberids["GetPointer"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        Opcode *first = new OPopRegister(new VarArgument(EXP1));
        first->setLabel(label);
        code.push_back(first);
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        code.push_back(new OGetFFCPointer(new VarArgument(EXP1)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label]=code;
    }
    
    //int SetPointer(ffc, float)
    {
        int id = memberids["SetPointer"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        Opcode *first = new OPopRegister(new VarArgument(EXP1));
        first->setLabel(label);
        code.push_back(first);
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        code.push_back(new OSetFFCPointer(new VarArgument(EXP1)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label]=code;
    }
    return rval;
		
		
	//void SetLinkTile(link, int,int,int)
    {
        int id = memberids["SetLinkTile"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        //pop off the params
        Opcode *first = new OPopRegister(new VarArgument(SFTEMP));
        first->setLabel(label);
        code.push_back(first);
        code.push_back(new OPopRegister(new VarArgument(INDEX2)));
        code.push_back(new OPopRegister(new VarArgument(INDEX)));
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        code.push_back(new OSetRegister(new VarArgument(SETLINKTILE), new VarArgument(SFTEMP)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label] = code;
    }
    
      //int GetLinkTile(link, int,int)
    {
        int id = memberids["GetLinkTile"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        //pop off the params
        Opcode *first = new OPopRegister(new VarArgument(INDEX2));
        first->setLabel(label);
        code.push_back(first);
        code.push_back(new OPopRegister(new VarArgument(INDEX)));
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SETLINKTILE)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label] = code;
    }
/void SetLinkExtend(link, int,int,int)
    {
        int id = memberids["SetLinkExtend"];
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
        code.push_back(new OSetRegister(new VarArgument(SETLINKEXTEND), new VarArgument(SFTEMP)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label] = code;
    }
    
    
     //void SetItemA(int)
    {
        int id = memberids["SetItemA"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        //pop off the params
        Opcode *first = new OPopRegister(new VarArgument(EXP2));
        first->setLabel(label);
        code.push_back(first);
        //code.push_back(new OPopRegister(new VarArgument(INDEX)));
        code.push_back(new OSetRegister(new VarArgument(GAMESETA), new VarArgument(EXP2)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label] = code;
    }
    
    {
	    int id = memberids["SetItemA"];
	    int label  = lt.functionToLabel(id);
	vector<Opcode *> code;
	//pop off the value to set to
	Opcode *first = new OPopRegister(new VarArgument(EXP1));
	first->setLabel(label);
	code.push_back(first);
	//pop object pointer
	code.push_back(new OPopRegister(new VarArgument(EXP2)));
	//load object pointer into ref register
	if(refVar!=NUL)
        code.push_back(new OSetRegister(new VarArgument(refVar), new VarArgument(EXP2)));
    code.push_back(new OSetRegister(new VarArgument(var), new VarArgument(EXP1)));
    code.push_back(new OPopRegister(new VarArgument(EXP2)));
    code.push_back(new OGotoRegister(new VarArgument(EXP2)));
    return code;
    }
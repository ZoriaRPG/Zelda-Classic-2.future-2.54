 //void SetScreenD(game, int,int,int)
    {
        int id = memberids["SetScreenD"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        //pop off the params
        Opcode *first = new OPopRegister(new VarArgument(SFTEMP));  //Why SFTEMP?
        first->setLabel(label);
        code.push_back(first);
        code.push_back(new OPopRegister(new VarArgument(INDEX2)));
        code.push_back(new OPopRegister(new VarArgument(INDEX)));
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        code.push_back(new OSetRegister(new VarArgument(SDDD), new VarArgument(SFTEMP)));  //Why SFTEMP?
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label] = code;
    }
      //int GetScreenD(game, int,int)
    {
        int id = memberids["GetScreenD"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        //pop off the params
        Opcode *first = new OPopRegister(new VarArgument(INDEX2));
        first->setLabel(label);
        code.push_back(first);
        code.push_back(new OPopRegister(new VarArgument(INDEX))); 
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(SDDD)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label] = code;
    }
    //The above uses SFTEMP, but the below does almost the same thing, and does now. What
    //precisely is SFTEMP used to do?
    
    //int GetComboCSet(int,int,int)
    {
        int id = memberids["GetComboCSet"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        //pop off the params
        Opcode *first = new OPopRegister(new VarArgument(INDEX));
        first->setLabel(label);
        code.push_back(first);
        code.push_back(new OPopRegister(new VarArgument(EXP1)));
        code.push_back(new OPopRegister(new VarArgument(INDEX2)));
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(COMBOCDM)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label] = code;
    }
    //void SetComboCSet(int,int,int,int)
    {
        int id = memberids["SetComboCSet"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        //pop off the params
        Opcode *first = new OPopRegister(new VarArgument(EXP2));
        first->setLabel(label);
        code.push_back(first);
        code.push_back(new OPopRegister(new VarArgument(INDEX)));
        code.push_back(new OPopRegister(new VarArgument(EXP1)));
        code.push_back(new OPopRegister(new VarArgument(INDEX2)));
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        code.push_back(new OSetRegister(new VarArgument(COMBOCDM), new VarArgument(EXP2)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label] = code;
    }
   
    
    //This uses an opcode. It takes two params, and returns one. 
    
      //void PlayEnhancedMusic(game, int, int)
    {
        int id = memberids["PlayEnhancedMusic"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        //pop off the params
        Opcode *first = new OPopRegister(new VarArgument(EXP1));
        first->setLabel(label);
        code.push_back(first);
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        code.push_back(new OPlayEnhancedMusic(new VarArgument(EXP2), new VarArgument(EXP1)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label] = code;
    }
    //whereas rhis takes three params, and returns one, but does not use a specific opcode.
    //It uses OSetReister, instead of a binary opcode. I presume this is because it takes three params?
    
      //int GetComboType(int,int,int)
    {
        int id = memberids["GetComboType"];
        int label = lt.functionToLabel(id);
        vector<Opcode *> code;
        //pop off the params
        Opcode *first = new OPopRegister(new VarArgument(INDEX));
        first->setLabel(label);
        code.push_back(first);
        code.push_back(new OPopRegister(new VarArgument(EXP1)));
        code.push_back(new OPopRegister(new VarArgument(INDEX2)));
        //pop pointer, and ignore it
        code.push_back(new OPopRegister(new VarArgument(NUL)));
        code.push_back(new OSetRegister(new VarArgument(EXP1), new VarArgument(COMBOTDM)));
        code.push_back(new OPopRegister(new VarArgument(EXP2)));
        code.push_back(new OGotoRegister(new VarArgument(EXP2)));
        rval[label] = code;
    }
    
    
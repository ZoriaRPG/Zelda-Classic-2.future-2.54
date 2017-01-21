//For ffscript.lpp

case	{doLines(); return CASE;}
switch	{doLines(); return SWITCH;}
npcdata {doLines(); return NPCDATA;}
\# { ; } //will be replaced by DIRECTIVE
\:			{ doLines();return COLON; }
\:\-        { doLines();return ASSIGN; } 
\:\:		{ doLines(); return ARROW;} //This is to be replaced by RESCOPE
define { doLines() return DEFINE; } //In the future, this should onyl work in the DIRECTIVE rule. 

//Comment block or comment
(/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+/)|(//.*) { ; }




/* Stuff that can surely wait. 
\!\<    {doLines(); return NOTLESS; }
\!\>    {doLines(); return NOTGREATER; }

\!\<\=    {doLines(); return NOTLESSOREQUAL; }
\!\>\=    {doLines(); return NOTGREATEROREQUAL; }
ptr { doLines(); return POINTER; }
until           { doLines(); return UNTIL; } 
unless          { doLines(); return UNLESS; } 
repeat          { doLines(); return REPEAT; }
begin          { doLines(); return BEGIN; }
end          { doLines(); return END; }
"/*" { commentblock(); }

void commentblock(void) {
	char c, prev = 0;
	while ( ( c = input() ) != 0 ) {
		if ( c == '/' && prev == '*' ) return;
		prev = c;
	}
}

*/



//For ffscript.ypp

//%token NPCDATA //for later

//If the simple token for ffscript.lpp doesn't work, we can fall back on a function. 
//%token COMMENTBLOCK

%token SWITCH
%token CASE
%token DEFINE

Type : FLOAT {$$ = new ASTTypeFloat(@1);}
	| BOOL {$$ = new ASTTypeBool(@1);}
	| VOID {$$ = new ASTTypeVoid(@1);}
	| FFC {$$ = new ASTTypeFFC(@1);}
	| ITEM {$$ = new ASTTypeItem(@1);}
	| ITEMCLASS {$$ = new ASTTypeItemclass(@1);}
	| NPC		{$$ = new ASTTypeNPC(@1);}
	| LWEAPON	{$$ = new ASTTypeLWpn(@1);}
	| EWEAPON	{$$ = new ASTTypeEWpn(@1);}
`	| NPCDATA {$$ = new ASTTypeNPCData(@1);}
	;

Stmt : VarDecl SEMICOLON {$$ = $1;}
	| ArrayDecl SEMICOLON {$$ = $1;}
	| AssignStmt SEMICOLON {$$ = $1;}
	| ShortcutAssignStmt SEMICOLON {$$=$1;}
	| ForStmt {$$ = $1;}
	| IfStmt {$$ = $1;}
	| Block {$$ = $1;}
	| ReturnStmt SEMICOLON {$$ = $1;}
	| WhileStmt {$$ = $1;}
	| DoStmt {$$ = $1;}
	| SwitchStmt {$$ = $1;}
	| SEMICOLON {$$ = new ASTStmtEmpty(@1);}
	| Expr SEMICOLON {$$=$1;}
	| BREAK SEMICOLON {$$ = new ASTStmtBreak(@1);}
	| CONTINUE SEMICOLON {$$ = new ASTStmtContinue(@1);}
	;

	
StmtNoSemi : VarDecl {$$ = $1;}
	| ArrayDecl {$$ = $1;}
	| AssignStmt {$$ = $1;}
	| ShortcutAssignStmt {$$=$1;}
	| ForStmt {$$ = $1;}
	| IfStmt {$$ = $1;}
	| Block {$$ = $1;}
	| ReturnStmt {$$ = $1;}
	| WhileStmt {$$ = $1;}
	| DoStmt {$$ = $1;}
	| {$$ = new ASTStmtEmpty(noloc);}
	| Expr {$$=$1;}
	| BREAK {$$ = new ASTStmtBreak(@1);}
	| CONTINUE {$$ = new ASTStmtContinue(@1);}
	| CASE  {$$ = new ASTStmtCase(@1);}
	;
	

DefineDecl : DEFINE IDENTIFIER NUMBER 	{ 	ASTString *name = (ASTString *)$3; 
						ASTFloat *val = (ASTFloat *)$5;
						$$ = new ASTtDecl(name->getValue(), val,@1);
						delete name;
					}
	|
		DEFINE IDENTIFIER MINUS NUMBER 	{  	ASTString *name = (ASTString *)$3;
							ASTFloat *val = (ASTFloat *)$6;
							val->set_negative(true);
							$$ = new ASTDefineDecl(name->getValue(), val,@1);
							delete name;
						}
					
	
ConstDecl : CONST FLOAT IDENTIFIER ASSIGN NUMBER SEMICOLON {ASTString *name = (ASTString *)$3;
															ASTFloat *val = (ASTFloat *)$5;
															$$ = new ASTConstDecl(name->getValue(), val,@1);
															delete name;}
          | CONST FLOAT IDENTIFIER ASSIGN MINUS NUMBER SEMICOLON {ASTString *name = (ASTString *)$3;
																  ASTFloat *val = (ASTFloat *)$6;
																  val->set_negative(true);
																  $$ = new ASTConstDecl(name->getValue(), val,@1);
																delete name;}
	| CONST FLOAT IDENTIFIER ASSIGN IDENTIFIER SEMICOLON 	{  ASTString *name = (ASTString *)$3;
								   ASTFloat *val = (ASTFloat *)$5;
								//This needs a check to find out of the value of the identifier
								//is negative! and to do
								// val->set_negative(true);
								   $$ = new ASTConstDecl(name->getValue(), val,@1);
								   delete name;
								}
	/*
          | CONST FLOAT IDENTIFIER ASSIGN MINUS IDENTIFIER SEMICOLON 	{ ASTString *name = (ASTString *)$3;
									  ASTFloat *val = (ASTFloat *)$6;
									  val->set_negative(true);
									  $$ = new ASTConstDecl(name->getValue(), val,@1);
									  delete name;
									}
	*/

Case Decl : CASE NUMBER COLON {ASTString *name = (ASTString *)$3;
	| CASE IDENTIFIER COLON {ASTString *name = (ASTString *)$3;
	

SwitchStmt : SWITCH LPAREN Expr RPAREN Stmt {ASTExpr *cond = (ASTExpr *)$3;
										   ASTStmt *stmt = (ASTStmt *)$5;
										   $$ = new ASTStmtWhile(cond,stmt,@1);}

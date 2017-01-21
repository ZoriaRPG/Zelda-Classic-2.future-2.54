">>="			{ count(); return(RIGHT_ASSIGN); }
"<<=" { count(); return(LEFT_ASSIGN); }

selection_statement
	: IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	| SWITCH '(' expression ')' statement
;

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN


"case" {  return(CASE); }
"switch"{ return(SWITCH);}

"case" {  dolines(); return CASE; }
"switch"{ dolines(); return SWITCH;}
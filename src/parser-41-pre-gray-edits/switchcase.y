Switch.Y
%{
    #include <stdio.h>
        void yyerror(char*msg);
    
%}

%token SWITCH BRO BRC CBO CBC CASE COLON BREAK DEFAULT ID DIGIT SEMI

%%

S: Statement {printf(“ACCEPTED”);}

Statement:SWITCH LPAREN IDENTIFIER RPAREN LBRACE CASEXPRESSION RBRACE

CASEXPRESSION: A
 | A C
 | A E

A: A B
 | CASE NUMBER D

B:  BREAK SEMI
 

C : DEFAULT D B
 

D : COLON IDENTIFIER SEMICOLON

 ;

%%

void yyerror(char *msg)
{
        
        {printf(“\n SWITHC Syntax is Wrong”);}
    
}
int main(void)
{
    yyparse();
        return 0;
}
SWITCH.Flex

%{
    #include “switch.tab.h”
    #include<stdlib.h>
%}

%%

[ \t\n]   
switch {return SWITCH;}

case {return CASE; }

“:” {return COLON; }

default {return DEFAULT;}

“;” {return SEMI;}

%%

int yywrap(void)

{

  return 1;

}

 

 
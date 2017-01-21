/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SRC_PARSER_Y_TAB_HPP_INCLUDED
# define YY_YY_SRC_PARSER_Y_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SCRIPT = 258,
    FLOAT = 259,
    FOR = 260,
    BOOL = 261,
    VOID = 262,
    IF = 263,
    ELSE = 264,
    RETURN = 265,
    IMPORT = 266,
    TRUE = 267,
    FALSE = 268,
    WHILE = 269,
    FFC = 270,
    ITEM = 271,
    ITEMCLASS = 272,
    GLOBAL = 273,
    BREAK = 274,
    CONTINUE = 275,
    CONST = 276,
    DO = 277,
    NPC = 278,
    LWEAPON = 279,
    EWEAPON = 280,
    ASSIGN = 281,
    SEMICOLON = 282,
    COMMA = 283,
    LBRACKET = 284,
    RBRACKET = 285,
    LPAREN = 286,
    RPAREN = 287,
    DOT = 288,
    LBRACE = 289,
    RBRACE = 290,
    ARROW = 291,
    NUMBER = 292,
    PLUSASSIGN = 293,
    MINUSASSIGN = 294,
    TIMESASSIGN = 295,
    DIVIDEASSIGN = 296,
    ANDASSIGN = 297,
    ORASSIGN = 298,
    BITANDASSIGN = 299,
    BITORASSIGN = 300,
    BITXORASSIGN = 301,
    MODULOASSIGN = 302,
    LSHIFTASSIGN = 303,
    RSHIFTASSIGN = 304,
    IDENTIFIER = 305,
    QUOTEDSTRING = 306,
    SINGLECHAR = 307,
    ATSIGN = 308,
    LSHIFT = 309,
    RSHIFT = 310,
    BITAND = 311,
    BITOR = 312,
    BITXOR = 313,
    AND = 314,
    OR = 315,
    NOT = 316,
    BITNOT = 317,
    INCREMENT = 318,
    DECREMENT = 319,
    LE = 320,
    LT = 321,
    GE = 322,
    GT = 323,
    EQ = 324,
    NE = 325,
    PLUS = 326,
    MINUS = 327,
    TIMES = 328,
    DIVIDE = 329,
    MODULO = 330
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_Y_TAB_HPP_INCLUDED  */

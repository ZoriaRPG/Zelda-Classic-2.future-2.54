/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 10 "src/parser/ffscript.ypp" /* yacc.c:339  */

#include <stdlib.h>
#include <stdio.h>
#include <cassert>
#include "AST.h"
#include "UtilVisitors.h"
#include "../zsyssimple.h"
#define YYINCLUDED_STDLIB_H
extern int yydebug;
extern int yylineno;
extern char* yytext;
extern int yylex(void);
extern FILE *yyin;
extern AST *resAST;
extern void resetLexer();
void yyerror(const char* s);
string curfilename;
extern YYLTYPE noloc;

#define SHORTCUT(x,d1,d3,dd,l1,l2) ASTExpr *lval = (ASTExpr *)d1; \
					Clone c; \
					lval->execute(c,NULL); \
					x *rhs = new x(l2); \
					rhs->setFirstOperand((ASTExpr *)c.getResult()); \
					rhs->setSecondOperand((ASTExpr *)d3); \
					dd = new ASTStmtAssign(lval, rhs, l1);

#line 94 "src/parser/y.tab.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.hpp".  */
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
    LSHIFT = 308,
    RSHIFT = 309,
    BITAND = 310,
    BITOR = 311,
    BITXOR = 312,
    AND = 313,
    OR = 314,
    NOT = 315,
    BITNOT = 316,
    INCREMENT = 317,
    DECREMENT = 318,
    LE = 319,
    LT = 320,
    GE = 321,
    GT = 322,
    EQ = 323,
    NE = 324,
    PLUS = 325,
    MINUS = 326,
    TIMES = 327,
    DIVIDE = 328,
    MODULO = 329
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

/* Copy the second part of user declarations.  */

#line 234 "src/parser/y.tab.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   525

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  157
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  270

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   329

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   107,   107,   110,   113,   116,   117,   118,   119,   120,
     121,   126,   129,   133,   139,   145,   151,   160,   174,   191,
     194,   199,   215,   216,   219,   224,   225,   228,   231,   236,
     237,   238,   243,   246,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   263,   272,   283,   286,   291,   292,   295,
     299,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   337,
     338,   339,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   352,   355,   356,   359,   363,   369,   377,   380,   384,
     392,   398,   401,   407,   410,   416,   419,   425,   428,   434,
     437,   443,   446,   452,   455,   456,   459,   460,   461,   462,
     463,   464,   467,   473,   476,   477,   480,   486,   489,   490,
     491,   494,   498,   502,   506,   509,   510,   511,   515,   519,
     523,   527,   529,   533,   534,   537,   538,   541,   545,   551,
     555,   561,   568,   572,   576,   579,   585,   586
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SCRIPT", "FLOAT", "FOR", "BOOL", "VOID",
  "IF", "ELSE", "RETURN", "IMPORT", "TRUE", "FALSE", "WHILE", "FFC",
  "ITEM", "ITEMCLASS", "GLOBAL", "BREAK", "CONTINUE", "CONST", "DO", "NPC",
  "LWEAPON", "EWEAPON", "ASSIGN", "SEMICOLON", "COMMA", "LBRACKET",
  "RBRACKET", "LPAREN", "RPAREN", "DOT", "LBRACE", "RBRACE", "ARROW",
  "NUMBER", "PLUSASSIGN", "MINUSASSIGN", "TIMESASSIGN", "DIVIDEASSIGN",
  "ANDASSIGN", "ORASSIGN", "BITANDASSIGN", "BITORASSIGN", "BITXORASSIGN",
  "MODULOASSIGN", "LSHIFTASSIGN", "RSHIFTASSIGN", "IDENTIFIER",
  "QUOTEDSTRING", "SINGLECHAR", "LSHIFT", "RSHIFT", "BITAND", "BITOR",
  "BITXOR", "AND", "OR", "NOT", "BITNOT", "INCREMENT", "DECREMENT", "LE",
  "LT", "GE", "GT", "EQ", "NE", "PLUS", "MINUS", "TIMES", "DIVIDE",
  "MODULO", "$accept", "Init", "Prog", "GlobalStmt", "ConstDecl",
  "ArrayDecl", "ArrayList", "Script", "ScriptType", "Import",
  "ScriptBlock", "ScriptStmtList", "ScriptStmt", "VarDecl", "Type",
  "FuncDecl", "ParamList", "Block", "StmtList", "Stmt", "StmtNoSemi",
  "ShortcutAssignStmt", "AssignStmt", "LVal", "DotExpr", "Expr", "Expr15",
  "Expr16", "Expr17", "Expr18", "Expr2", "Expr25", "ShiftOp", "RelOp",
  "Expr3", "AddOp", "Expr4", "MultOp", "Expr5", "Factor", "BoolConstant",
  "FuncCall", "ExprList", "ForStmt", "WhileStmt", "DoStmt", "IfStmt",
  "ReturnStmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329
};
# endif

#define YYPACT_NINF -182

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-182)))

#define YYTABLE_NINF -94

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -182,    23,   500,  -182,  -182,  -182,  -182,   -13,  -182,  -182,
    -182,  -182,    31,  -182,  -182,  -182,  -182,  -182,    30,  -182,
      76,  -182,     6,    51,  -182,  -182,    60,  -182,    63,   177,
    -182,    -5,    55,    85,  -182,  -182,   177,  -182,    83,  -182,
     177,   177,    71,    71,   177,    34,     3,    66,    90,    95,
      98,    62,    45,    64,    77,  -182,  -182,  -182,  -182,   -12,
     227,   -16,   462,  -182,    43,   177,   104,  -182,  -182,   119,
     119,  -182,   110,   106,  -182,  -182,  -182,   177,   177,   177,
     177,   177,  -182,  -182,  -182,  -182,  -182,  -182,   177,  -182,
    -182,   177,  -182,  -182,   177,  -182,  -182,  -182,   177,   131,
     128,   125,   133,   113,   132,   138,   130,  -182,   141,   134,
     291,   117,    51,  -182,  -182,    41,   145,  -182,     0,   143,
     147,    66,    90,    95,    98,    62,    45,    64,    77,  -182,
     -17,   152,   259,  -182,   291,  -182,   125,  -182,   156,  -182,
    -182,  -182,   177,  -182,  -182,   177,   177,  -182,   177,   177,
    -182,    44,   153,   154,   177,   157,   164,   165,   379,  -182,
    -182,   179,   180,   159,  -182,   319,  -182,   183,   185,   187,
       5,    10,  -182,  -182,  -182,  -182,   188,  -182,  -182,  -182,
      13,    46,  -182,    47,    -6,   160,   177,  -182,   439,   177,
     160,   177,  -182,  -182,   204,  -182,  -182,   191,  -182,  -182,
    -182,  -182,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,  -182,  -182,  -182,  -182,  -182,
     177,  -182,    59,  -182,  -182,  -182,   195,  -182,   198,  -182,
    -182,   160,  -182,  -182,  -182,  -182,  -182,    48,    58,   199,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   160,
     160,   160,   160,   160,  -182,   177,   379,   379,   177,    15,
     213,  -182,    61,   439,   379,  -182,   194,  -182,   379,  -182
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,    34,    35,    36,     0,    37,    38,
      39,    23,     0,    40,    41,    42,     3,     8,     0,     5,
       0,     6,     0,    22,     7,    24,     0,    11,     0,     0,
       9,    33,     0,     0,   145,   146,     0,   141,    97,   142,
       0,     0,     0,     0,     0,   136,     0,   101,   103,   105,
     107,   109,   111,   113,   123,   127,   134,   143,   144,     0,
       0,     0,     0,    21,     0,     0,     0,   131,   133,   138,
     140,   132,     0,     0,   137,   139,    10,     0,     0,     0,
       0,     0,   119,   118,   117,   116,   120,   121,     0,   114,
     115,     0,   124,   125,     0,   128,   129,   130,     0,     0,
       0,     0,    46,     0,     0,     0,     0,    26,     0,     0,
      28,     0,     0,    32,   135,     0,    94,   148,   150,     0,
      98,   100,   102,   104,   106,   108,   110,   112,   122,   126,
       0,    14,     0,    44,     0,    33,     0,    12,     0,    30,
      25,    27,     0,    29,    95,     0,     0,   147,     0,     0,
      18,     0,     0,     0,   157,     0,     0,     0,     0,    61,
      48,     0,    92,     0,    57,     0,    50,     0,     0,     0,
     136,     0,    55,    59,    60,    56,     0,    45,    43,    13,
       0,     0,   149,     0,     0,    20,     0,    17,    75,     0,
     156,     0,    63,    64,     0,    52,    51,    33,    47,    49,
      54,    53,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    62,    58,    31,    96,    99,
       0,    16,     0,    77,    78,    66,    65,    71,     0,    68,
      67,    76,    69,    73,    74,    70,    72,     0,     0,     0,
      91,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      90,    88,    89,    19,    15,     0,     0,     0,     0,     0,
     154,   152,     0,    75,     0,   153,     0,   155,     0,   151
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -182,  -182,  -182,  -182,  -182,    -1,    49,  -182,  -182,  -182,
    -182,   122,  -182,    -2,     4,   234,   107,   -97,  -182,  -153,
     -18,  -181,  -180,  -182,   -40,    -9,   170,   175,   176,   178,
     189,   168,  -182,  -182,   166,  -182,   174,  -182,   -25,  -182,
    -182,  -182,   114,  -179,  -178,  -177,  -175,  -174
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    16,    17,   161,   184,    19,    20,    21,
      63,   109,   110,   162,   163,   113,   104,   164,   165,   166,
     228,   167,   168,   169,    45,   171,    47,    48,    49,    50,
      51,    52,    91,    88,    53,    94,    54,    98,    55,    56,
      57,    58,   119,   172,   173,   174,   175,   176
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      22,    18,    69,    70,   133,   194,    23,   229,   230,   232,
     233,   234,   199,   235,   236,    67,    68,   149,    99,    71,
      46,   105,   220,     3,    59,   100,    60,    64,   146,   221,
      76,   -93,    29,    30,   150,    26,    72,   215,    25,   178,
     217,    73,   263,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   106,   115,    27,   102,    77,
     111,   108,    77,   118,   103,    72,   112,    74,    75,    77,
      73,   144,    77,   129,    77,   114,   218,   219,   186,    28,
     256,    61,   229,   230,   232,   233,   234,   220,   235,   236,
     257,   227,   170,   265,   254,   187,    74,    75,    89,    90,
      77,    31,    77,   260,   261,    77,    77,    77,   111,   108,
      32,   267,    65,    33,   112,   269,    66,    77,   170,    62,
      77,    38,    34,    35,    78,   170,    82,    83,    84,    85,
      86,    87,   102,   180,    92,    93,   181,   118,   103,   183,
     185,    36,   117,   142,   143,   190,    79,    37,   170,    95,
      96,    97,    80,    81,   116,    73,   120,   130,   131,   132,
      38,   134,    39,   135,   136,   137,   227,   138,   139,   140,
      40,    41,    42,    43,   145,   147,   148,   185,   151,   231,
     237,    44,   238,   179,   188,   189,   226,   225,   191,    34,
      35,   192,   193,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   195,   196,    36,   197,
     200,   253,   201,   202,    37,   216,   170,   170,   239,    77,
      59,   -92,   264,   170,   170,   255,   268,    38,   170,    39,
     258,     4,   141,     5,     6,   222,    24,    40,    41,    42,
      43,   177,     8,     9,    10,   266,   259,   121,    44,   262,
      13,    14,    15,   122,   231,   123,   126,   127,   124,   101,
     182,   226,   225,     4,   152,     5,     6,   153,   128,   154,
     125,    34,    35,   155,     8,     9,    10,     0,   156,   157,
       0,   158,    13,    14,    15,     0,   159,     0,     0,     0,
      36,     0,     0,   132,   160,     4,    37,     5,     6,     0,
       0,     0,     0,     0,     0,     0,     8,     9,    10,    38,
       0,    39,     0,     0,    13,    14,    15,     0,     0,    40,
      41,    42,    43,     4,   152,     5,     6,   153,     0,   154,
      44,    34,    35,   155,     8,     9,    10,     0,   156,   157,
       0,   158,    13,    14,    15,     0,   159,     0,     0,     0,
      36,     0,     0,   132,   198,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,    39,     0,     0,     0,     0,     0,     0,     0,    40,
      41,    42,    43,     4,   152,     5,     6,   153,     0,   154,
      44,    34,    35,   155,     8,     9,    10,     0,   156,   157,
       0,   158,    13,    14,    15,     0,   159,     0,     0,     0,
      36,     0,     0,   132,     0,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,    39,     0,     0,     0,     0,     0,     0,     0,    40,
      41,    42,    43,     4,   152,     5,     6,   153,     0,   154,
      44,    34,    35,   155,     8,     9,    10,     0,   223,   224,
       0,   158,    13,    14,    15,     0,     4,     0,     5,     6,
      36,     0,     0,   132,     0,     0,    37,     8,     9,    10,
       0,     0,     0,     0,     0,    13,    14,    15,     0,    38,
       0,    39,     0,     0,     0,     0,     0,   107,     0,    40,
      41,    42,    43,     0,     4,     0,     5,     6,     0,     0,
      44,     7,     0,     0,     0,     8,     9,    10,    11,     0,
       0,    12,     0,    13,    14,    15
};

static const yytype_int16 yycheck[] =
{
       2,     2,    42,    43,   101,   158,     2,   188,   188,   188,
     188,   188,   165,   188,   188,    40,    41,    34,    30,    44,
      29,    37,    28,     0,    29,    37,    31,    36,    28,    35,
      27,    26,    26,    27,    51,     4,    31,    27,    51,   136,
      27,    36,    27,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    71,    65,    27,    60,    59,
      62,    62,    59,    72,    60,    31,    62,    62,    63,    59,
      36,    30,    59,    98,    59,    32,    30,    30,    34,     3,
      32,    26,   263,   263,   263,   263,   263,    28,   263,   263,
      32,   188,   132,    32,    35,    51,    62,    63,    53,    54,
      59,    50,    59,   256,   257,    59,    59,    59,   110,   110,
      50,   264,    29,    50,   110,   268,    33,    59,   158,    34,
      59,    50,    12,    13,    58,   165,    64,    65,    66,    67,
      68,    69,   134,   142,    70,    71,   145,   146,   134,   148,
     149,    31,    32,    26,    27,   154,    56,    37,   188,    72,
      73,    74,    57,    55,    50,    36,    50,    26,    30,    34,
      50,    28,    52,    50,    32,    27,   263,    37,    27,    35,
      60,    61,    62,    63,    29,    32,    29,   186,    26,   188,
     189,    71,   191,    27,    31,    31,   188,   188,    31,    12,
      13,    27,    27,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,    27,    27,    31,    50,
      27,   220,    27,    26,    37,    27,   256,   257,    14,    59,
      29,    26,     9,   263,   264,    27,    32,    50,   268,    52,
      31,     4,   110,     6,     7,   186,     2,    60,    61,    62,
      63,   134,    15,    16,    17,   263,   255,    77,    71,   258,
      23,    24,    25,    78,   263,    79,    88,    91,    80,    32,
     146,   263,   263,     4,     5,     6,     7,     8,    94,    10,
      81,    12,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    22,    23,    24,    25,    -1,    27,    -1,    -1,    -1,
      31,    -1,    -1,    34,    35,     4,    37,     6,     7,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,    50,
      -1,    52,    -1,    -1,    23,    24,    25,    -1,    -1,    60,
      61,    62,    63,     4,     5,     6,     7,     8,    -1,    10,
      71,    12,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    22,    23,    24,    25,    -1,    27,    -1,    -1,    -1,
      31,    -1,    -1,    34,    35,    -1,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,     4,     5,     6,     7,     8,    -1,    10,
      71,    12,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    22,    23,    24,    25,    -1,    27,    -1,    -1,    -1,
      31,    -1,    -1,    34,    -1,    -1,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,     4,     5,     6,     7,     8,    -1,    10,
      71,    12,    13,    14,    15,    16,    17,    -1,    19,    20,
      -1,    22,    23,    24,    25,    -1,     4,    -1,     6,     7,
      31,    -1,    -1,    34,    -1,    -1,    37,    15,    16,    17,
      -1,    -1,    -1,    -1,    -1,    23,    24,    25,    -1,    50,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    35,    -1,    60,
      61,    62,    63,    -1,     4,    -1,     6,     7,    -1,    -1,
      71,    11,    -1,    -1,    -1,    15,    16,    17,    18,    -1,
      -1,    21,    -1,    23,    24,    25
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    76,    77,     0,     4,     6,     7,    11,    15,    16,
      17,    18,    21,    23,    24,    25,    78,    79,    80,    82,
      83,    84,    88,    89,    90,    51,     4,    27,     3,    26,
      27,    50,    50,    50,    12,    13,    31,    37,    50,    52,
      60,    61,    62,    63,    71,    99,   100,   101,   102,   103,
     104,   105,   106,   109,   111,   113,   114,   115,   116,    29,
      31,    26,    34,    85,   100,    29,    33,   113,   113,    99,
      99,   113,    31,    36,    62,    63,    27,    59,    58,    56,
      57,    55,    64,    65,    66,    67,    68,    69,   108,    53,
      54,   107,    70,    71,   110,    72,    73,    74,   112,    30,
      37,    32,    88,    89,    91,    37,    71,    35,    80,    86,
      87,    88,    89,    90,    32,   100,    50,    32,   100,   117,
      50,   101,   102,   103,   104,   105,   106,   109,   111,   113,
      26,    30,    34,    92,    28,    50,    32,    27,    37,    27,
      35,    86,    26,    27,    30,    29,    28,    32,    29,    34,
      51,    26,     5,     8,    10,    14,    19,    20,    22,    27,
      35,    80,    88,    89,    92,    93,    94,    96,    97,    98,
      99,   100,   118,   119,   120,   121,   122,    91,    92,    27,
     100,   100,   117,   100,    81,   100,    34,    51,    31,    31,
     100,    31,    27,    27,    94,    27,    27,    50,    35,    94,
      27,    27,    26,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    27,    27,    27,    30,    30,
      28,    35,    81,    19,    20,    80,    88,    92,    95,    96,
      97,   100,   118,   119,   120,   121,   122,   100,   100,    14,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   100,   100,   100,    35,    27,    32,    32,    31,   100,
      94,    94,   100,    27,     9,    32,    95,    94,    32,    94
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    75,    76,    77,    77,    78,    78,    78,    78,    78,
      78,    78,    79,    79,    80,    80,    80,    80,    80,    81,
      81,    82,    83,    83,    84,    85,    85,    86,    86,    87,
      87,    87,    87,    88,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    90,    90,    91,    91,    92,    92,    93,
      93,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    97,    98,    98,    99,    99,    99,    99,    99,    99,
     100,   100,   101,   101,   102,   102,   103,   103,   104,   104,
     105,   105,   106,   106,   107,   107,   108,   108,   108,   108,
     108,   108,   109,   109,   110,   110,   111,   111,   112,   112,
     112,   113,   113,   113,   113,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   115,   115,   116,   116,   117,
     117,   118,   119,   120,   121,   121,   122,   122
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     1,     2,
       4,     2,     6,     7,     5,     9,     8,     7,     6,     3,
       1,     4,     1,     1,     2,     3,     2,     2,     1,     2,
       2,     4,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     6,     5,     3,     1,     3,     2,     2,
       1,     2,     2,     2,     2,     1,     1,     1,     2,     1,
       1,     1,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     1,     3,     4,     6,     1,     3,     6,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       1,     2,     2,     2,     1,     3,     1,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     4,     3,     3,
       1,     9,     5,     6,     5,     7,     2,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 107 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {resAST = new ASTProgram((ASTDeclList *)(yyvsp[0]), (yylsp[0]));}
#line 1661 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 110 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTDeclList *list = (ASTDeclList *)(yyvsp[-1]);
				list->addDeclaration((ASTDecl *)(yyvsp[0]));
				(yyval) = list;}
#line 1669 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 113 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTDeclList(noloc);}
#line 1675 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 116 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1681 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 117 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1687 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 118 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1693 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 119 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1699 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 120 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 1705 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 121 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTVarDecl *vd = (ASTVarDecl *)(yyvsp[-3]);
									Clone c;
									vd->getType()->execute(c,NULL);
									(yyval) = new ASTVarDeclInitializer((ASTType *)c.getResult(), vd->getName(), (ASTExpr *)(yyvsp[-1]),(yylsp[-3]));
									delete vd;}
#line 1715 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 126 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 1721 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 129 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTString *name = (ASTString *)(yyvsp[-3]);
															ASTFloat *val = (ASTFloat *)(yyvsp[-1]);
															(yyval) = new ASTConstDecl(name->getValue(), val,(yylsp[-5]));
															delete name;}
#line 1730 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 133 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTString *name = (ASTString *)(yyvsp[-4]);
																  ASTFloat *val = (ASTFloat *)(yyvsp[-1]);
																  val->set_negative(true);
																  (yyval) = new ASTConstDecl(name->getValue(), val,(yylsp[-6]));
																  delete name;}
#line 1740 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 139 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {	ASTType *type = (ASTType *)(yyvsp[-4]);
														ASTString *name = (ASTString *)(yyvsp[-3]);
														ASTExpr *size = (ASTExpr *)(yyvsp[-1]);
														(yyval) = new ASTArrayDecl(type, name->getValue(), size, false, NULL, (yylsp[-4]));
														delete name;}
#line 1750 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 145 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {	ASTType *type = (ASTType *)(yyvsp[-8]);
																				ASTString *name = (ASTString *)(yyvsp[-7]);
																				ASTFloat *size = (ASTFloat *)(yyvsp[-5]);
																				ASTArrayList *list = (ASTArrayList *)(yyvsp[-1]);
																				(yyval) = new ASTArrayDecl(type, name->getValue(), size, false, list, (yylsp[-8]));
																				delete name;}
#line 1761 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 151 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {	ASTType *type = (ASTType *)(yyvsp[-7]);
																			ASTString *name = (ASTString *)(yyvsp[-6]);
																			ASTArrayList *list = (ASTArrayList *)(yyvsp[-1]);
																			char val[15];
																			sprintf(val, "%d", list->getList().size());
																			ASTFloat *size = new ASTFloat(val, 0, (yylsp[-7]));
																			(yyval) = new ASTArrayDecl(type, name->getValue(), size, false, list, (yylsp[-7]));
																			delete name;}
#line 1774 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 160 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {	ASTType *type = (ASTType *)(yyvsp[-6]);
																		ASTString *name = (ASTString *)(yyvsp[-5]);
																		ASTFloat *size = (ASTFloat *)(yyvsp[-3]);
																		ASTArrayList *list = new ASTArrayList((yylsp[-6]));
																		list->makeString();
																		ASTString *string = (ASTString *)(yyvsp[0]);

																		for(unsigned int i=1; i < string->getValue().length()-1; i++)
																			list->addParam(new ASTNumConstant(new ASTFloat(long((string->getValue())[i]), 0, (yylsp[-6])), (yylsp[-6])));

																		list->addParam(new ASTNumConstant(new ASTFloat(0L, 0, (yylsp[-6])), (yylsp[-6])));
																		(yyval) = new ASTArrayDecl(type, name->getValue(), size, false, list, (yylsp[-6]));
																		delete name;}
#line 1792 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 174 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {	ASTType *type = (ASTType *)(yyvsp[-5]);
																ASTString *name = (ASTString *)(yyvsp[-4]);
																ASTArrayList *list = new ASTArrayList((yylsp[-5]));
																list->makeString();
																ASTString *string = (ASTString *)(yyvsp[0]);
																ASTFloat *size = new ASTFloat(string->getValue().length()-1, 0, (yylsp[-5]));

																for(unsigned int i=1; i < string->getValue().length()-1; i++)
																	list->addParam(new ASTNumConstant(new ASTFloat(long((string->getValue())[i]), 0, (yylsp[-5])), (yylsp[-5])));

																list->addParam(new ASTNumConstant(new ASTFloat(0L, 0, (yylsp[-5])), (yylsp[-5])));
																(yyval) = new ASTArrayDecl(type, name->getValue(), size, false, list, (yylsp[-5]));
																delete name;}
#line 1810 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 191 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {	ASTArrayList *al = (ASTArrayList *)(yyvsp[-2]);
									al->addParam((ASTExpr*)(yyvsp[0]));
									(yyval)=al;}
#line 1818 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 194 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {	ASTArrayList *al = new ASTArrayList((yylsp[0]));
				al->addParam((ASTExpr *)(yyvsp[0]));
				(yyval)=al;}
#line 1826 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 199 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTType *type = (ASTType *)(yyvsp[-3]);
												   int scripttype; //Itemdata pointer instead of item pointer
												   ExtractType temp;
												   type->execute(temp, &scripttype);
												   if(scripttype == ScriptParser::TYPE_ITEM)
												   {
													  ASTType *t = type; //so we can keep the locationdata before deleting
													  type = new ASTTypeItemclass(type->getLocation());
													  delete t;
												   }
												   ASTString *name = (ASTString *)(yyvsp[-1]);
												   ASTDeclList *sblock = (ASTDeclList *)(yyvsp[0]);
												   (yyval) = new ASTScript(type, name->getValue(), sblock,(yylsp[-3]));
												   delete name;}
#line 1845 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 215 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1851 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 216 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTTypeGlobal((yylsp[0]));}
#line 1857 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 219 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTString *str = (ASTString *)(yyvsp[0]);
								 (yyval) = new ASTImportDecl(str->getValue(),(yylsp[-1]));
								 delete str;}
#line 1865 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 224 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 1871 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 225 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTDeclList((yylsp[-1]));}
#line 1877 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 228 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTDeclList *dl = (ASTDeclList *)(yyvsp[0]);
											dl->addDeclaration((ASTDecl *)(yyvsp[-1]));
											(yyval) = dl;}
#line 1885 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 231 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {	ASTDeclList *dl = new ASTDeclList((yylsp[0]));
					dl->addDeclaration((ASTDecl *)(yyvsp[0]));
					(yyval) = dl;}
#line 1893 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 236 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 1899 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 237 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 1905 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 238 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTVarDecl *vd = (ASTVarDecl *)(yyvsp[-3]);
						   Clone c;
						   vd->getType()->execute(c,NULL);
						   (yyval) = new ASTVarDeclInitializer((ASTType *)c.getResult(), vd->getName(), (ASTExpr *)(yyvsp[-1]),(yylsp[-3]));
						   delete vd;}
#line 1915 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 243 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 1921 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 246 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTType *type = (ASTType *)(yyvsp[-1]);
				   ASTString *name = (ASTString *)(yyvsp[0]);
				   (yyval) = new ASTVarDecl(type, name->getValue(),(yylsp[-1]));
				   delete name;}
#line 1930 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 252 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTTypeFloat((yylsp[0]));}
#line 1936 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 253 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTTypeBool((yylsp[0]));}
#line 1942 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 254 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTTypeVoid((yylsp[0]));}
#line 1948 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 255 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTTypeFFC((yylsp[0]));}
#line 1954 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 256 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTTypeItem((yylsp[0]));}
#line 1960 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 257 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTTypeItemclass((yylsp[0]));}
#line 1966 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 258 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTTypeNPC((yylsp[0]));}
#line 1972 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 259 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTTypeLWpn((yylsp[0]));}
#line 1978 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 260 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTTypeEWpn((yylsp[0]));}
#line 1984 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 263 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTFuncDecl *fd = (ASTFuncDecl *)(yyvsp[-2]);
									    ASTType *rettype = (ASTType *)(yyvsp[-5]);
									    ASTString *name = (ASTString *)(yyvsp[-4]);
									    ASTBlock *block = (ASTBlock *)(yyvsp[0]);
									    fd->setName(name->getValue());
									    delete name;
									    fd->setReturnType(rettype);
									    fd->setBlock(block);
									    (yyval)=fd;}
#line 1998 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 272 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTFuncDecl *fd = new ASTFuncDecl((yylsp[-4]));
							   ASTType *rettype = (ASTType *)(yyvsp[-4]);
							   ASTString *name = (ASTString *)(yyvsp[-3]);
							   ASTBlock *block = (ASTBlock *)(yyvsp[0]);
							   fd->setName(name->getValue());
							   delete name;
							   fd->setReturnType(rettype);
							   fd->setBlock(block);
							   (yyval)=fd;}
#line 2012 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 283 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTFuncDecl *fd = (ASTFuncDecl *)(yyvsp[0]);
						 fd->addParam((ASTVarDecl *)(yyvsp[-2]));
						 (yyval)=fd;}
#line 2020 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 286 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTFuncDecl *fd = new ASTFuncDecl((yylsp[0]));
		     fd->addParam((ASTVarDecl *)(yyvsp[0]));
		     (yyval)=fd;}
#line 2028 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 291 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);}
#line 2034 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 292 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTBlock((yylsp[-1]));}
#line 2040 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 295 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTBlock *block = (ASTBlock *)(yyvsp[-1]);
				  ASTStmt *stmt = (ASTStmt *)(yyvsp[0]);
				  block->addStatement(stmt);
				  (yyval) = block;}
#line 2049 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 299 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTBlock *block = new ASTBlock((yylsp[0]));
		  ASTStmt *stmt = (ASTStmt *)(yyvsp[0]);
		  block->addStatement(stmt);
		  (yyval) = block;}
#line 2058 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 305 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 2064 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 306 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 2070 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 307 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 2076 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 308 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);}
#line 2082 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 309 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2088 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 310 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2094 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 311 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2100 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 312 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 2106 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 313 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2112 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 314 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2118 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 315 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTStmtEmpty((yylsp[0]));}
#line 2124 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 316 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);}
#line 2130 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 317 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTStmtBreak((yylsp[-1]));}
#line 2136 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 318 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTStmtContinue((yylsp[-1]));}
#line 2142 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 321 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2148 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 322 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2154 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 323 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2160 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 324 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 2166 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 325 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2172 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 326 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2178 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 327 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2184 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 328 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2190 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 329 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2196 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 330 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2202 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 331 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTStmtEmpty(noloc);}
#line 2208 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 332 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 2214 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 333 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTStmtBreak((yylsp[0]));}
#line 2220 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 334 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTStmtContinue((yylsp[0]));}
#line 2226 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 337 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {SHORTCUT(ASTExprPlus,(yyvsp[-2]),(yyvsp[0]),(yyval),(yylsp[-2]),(yylsp[-1])) }
#line 2232 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 338 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {SHORTCUT(ASTExprMinus,(yyvsp[-2]),(yyvsp[0]),(yyval),(yylsp[-2]),(yylsp[-1])) }
#line 2238 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 339 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {SHORTCUT(ASTExprTimes,(yyvsp[-2]),(yyvsp[0]),(yyval),(yylsp[-2]),(yylsp[-1])) }
#line 2244 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 340 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {SHORTCUT(ASTExprDivide,(yyvsp[-2]),(yyvsp[0]),(yyval),(yylsp[-2]),(yylsp[-1])) }
#line 2250 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 341 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {SHORTCUT(ASTExprAnd,(yyvsp[-2]),(yyvsp[0]),(yyval),(yylsp[-2]),(yylsp[-1])) }
#line 2256 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 342 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {SHORTCUT(ASTExprOr,(yyvsp[-2]),(yyvsp[0]),(yyval),(yylsp[-2]),(yylsp[-1])) }
#line 2262 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 343 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {SHORTCUT(ASTExprBitAnd,(yyvsp[-2]),(yyvsp[0]),(yyval),(yylsp[-2]),(yylsp[-1])) }
#line 2268 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 344 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {SHORTCUT(ASTExprBitOr,(yyvsp[-2]),(yyvsp[0]),(yyval),(yylsp[-2]),(yylsp[-1])) }
#line 2274 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 345 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {SHORTCUT(ASTExprBitXor,(yyvsp[-2]),(yyvsp[0]),(yyval),(yylsp[-2]),(yylsp[-1])) }
#line 2280 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 346 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {SHORTCUT(ASTExprLShift,(yyvsp[-2]),(yyvsp[0]),(yyval),(yylsp[-2]),(yylsp[-1])) }
#line 2286 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 347 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {SHORTCUT(ASTExprRShift,(yyvsp[-2]),(yyvsp[0]),(yyval),(yylsp[-2]),(yylsp[-1])) }
#line 2292 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 348 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {SHORTCUT(ASTExprModulo,(yyvsp[-2]),(yyvsp[0]),(yyval),(yylsp[-2]),(yylsp[-1])) }
#line 2298 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 352 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTStmtAssign((ASTStmt *)(yyvsp[-2]), (ASTExpr *)(yyvsp[0]),(yylsp[-2]));}
#line 2304 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 355 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2310 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 356 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2316 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 359 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTString *lval = (ASTString *)(yyvsp[-2]);
						 ASTString *rval = (ASTString *)(yyvsp[0]);
						 (yyval) = new ASTExprDot(lval->getValue(), rval->getValue(),(yylsp[-2]));
						 delete lval; delete rval;}
#line 2325 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 363 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    { ASTString *name = (ASTString *)(yyvsp[-3]);
										ASTExpr *num = (ASTExpr *)(yyvsp[-1]);
										ASTExprArray *ar = new ASTExprArray("", name->getValue(), (yylsp[-3]));
										ar->setIndex(num);
										(yyval) = ar;
										delete name;}
#line 2336 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 369 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    { ASTString *name = (ASTString *)(yyvsp[-5]);
										ASTString *name2 = (ASTString *)(yyvsp[-3]);
										ASTExpr *num = (ASTExpr *)(yyvsp[-1]);
										ASTExprArray *ar = new ASTExprArray(name->getValue(), name2->getValue(), (yylsp[-5]));
										ar->setIndex(num);
										(yyval) = ar;
										delete name;
										delete name2;}
#line 2349 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 377 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTString *rval = (ASTString *)(yyvsp[0]);
				  (yyval) = new ASTExprDot("", rval->getValue(),(yylsp[0]));
				  delete rval;}
#line 2357 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 380 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTExpr *id = (ASTExpr *)(yyvsp[-2]);
								ASTString *rval = (ASTString *)(yyvsp[0]);
								(yyval) = new ASTExprArrow(id, rval->getValue(), (yylsp[-2]));
								delete rval;}
#line 2366 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 384 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTExpr *id = (ASTExpr *)(yyvsp[-5]);
											       	   ASTString *rval = (ASTString *)(yyvsp[-3]);
													   ASTExpr *num = (ASTExpr *)(yyvsp[-1]);
													   ASTExprArrow *res = new ASTExprArrow(id, rval->getValue(), (yylsp[-5]));
													   res->setIndex(num);
													   (yyval) = res;}
#line 2377 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 392 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTLogExpr *e = new ASTExprOr((yylsp[-1]));
				 ASTExpr *left = (ASTExpr *)(yyvsp[-2]);
				 ASTExpr *right = (ASTExpr *)(yyvsp[0]);
				 e->setFirstOperand(left);
				 e->setSecondOperand(right);
				 (yyval)=e;}
#line 2388 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 398 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 2394 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 401 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTLogExpr *e = new ASTExprAnd((yylsp[-1]));
				 ASTExpr *left = (ASTExpr *)(yyvsp[-2]);
				 ASTExpr *right = (ASTExpr *)(yyvsp[0]);
				 e->setFirstOperand(left);
				 e->setSecondOperand(right);
				 (yyval)=e;}
#line 2405 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 407 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 2411 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 410 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTBitExpr *e = new ASTExprBitOr((yylsp[-1]));
							  ASTExpr *left = (ASTExpr *)(yyvsp[-2]);
							  ASTExpr *right = (ASTExpr *)(yyvsp[0]);
							  e->setFirstOperand(left);
							  e->setSecondOperand(right);
							  (yyval)=e;}
#line 2422 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 416 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 2428 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 419 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTBitExpr *e = new ASTExprBitXor((yylsp[-1]));
							   ASTExpr *left = (ASTExpr *)(yyvsp[-2]);
							   ASTExpr *right = (ASTExpr *)(yyvsp[0]);
							   e->setFirstOperand(left);
							   e->setSecondOperand(right);
							   (yyval)=e;}
#line 2439 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 425 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2445 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 428 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTBitExpr *e = new ASTExprBitAnd((yylsp[-1]));
							   ASTExpr *left = (ASTExpr *)(yyvsp[-2]);
							   ASTExpr *right = (ASTExpr *)(yyvsp[0]);
							   e->setFirstOperand(left);
							   e->setSecondOperand(right);
							   (yyval)=e;}
#line 2456 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 434 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 2462 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 437 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTRelExpr *e = (ASTRelExpr *)(yyvsp[-1]);
				   ASTExpr *left = (ASTExpr *)(yyvsp[-2]);
				   ASTExpr *right = (ASTExpr *)(yyvsp[0]);
				   e->setFirstOperand(left);
				   e->setSecondOperand(right);
				   (yyval)=e;}
#line 2473 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 443 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2479 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 446 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTShiftExpr *e = (ASTShiftExpr *)(yyvsp[-1]);
							   ASTExpr *left = (ASTExpr *)(yyvsp[-2]);
							   ASTExpr *right = (ASTExpr *)(yyvsp[0]);
							   e->setFirstOperand(left);
							   e->setSecondOperand(right);
							   (yyval)=e;}
#line 2490 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 452 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 2496 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 455 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTExprLShift((yylsp[0]));}
#line 2502 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 456 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTExprRShift((yylsp[0]));}
#line 2508 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 459 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTExprGT((yylsp[0]));}
#line 2514 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 460 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTExprGE((yylsp[0]));}
#line 2520 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 461 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTExprLT((yylsp[0]));}
#line 2526 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 462 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTExprLE((yylsp[0]));}
#line 2532 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 463 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTExprEQ((yylsp[0]));}
#line 2538 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 464 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTExprNE((yylsp[0]));}
#line 2544 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 467 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTAddExpr *e = (ASTAddExpr *)(yyvsp[-1]);
				   ASTExpr *left = (ASTExpr *)(yyvsp[-2]);
				   ASTExpr *right = (ASTExpr *)(yyvsp[0]);
				   e->setFirstOperand(left);
				   e->setSecondOperand(right);
				   (yyval)=e;}
#line 2555 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 473 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2561 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 476 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTExprPlus((yylsp[0]));}
#line 2567 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 477 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTExprMinus((yylsp[0]));}
#line 2573 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 480 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTMultExpr *e = (ASTMultExpr *)(yyvsp[-1]);
				    ASTExpr *left = (ASTExpr *)(yyvsp[-2]);
				    ASTExpr *right = (ASTExpr *)(yyvsp[0]);
				    e->setFirstOperand(left);
				    e->setSecondOperand(right);
				    (yyval)=e;}
#line 2584 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 486 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 2590 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 489 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTExprTimes((yylsp[0]));}
#line 2596 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 490 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTExprDivide((yylsp[0]));}
#line 2602 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 491 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTExprModulo((yylsp[0]));}
#line 2608 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 494 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTUnaryExpr *e = new ASTExprNot((yylsp[-1]));
			 ASTExpr *op = (ASTExpr *)(yyvsp[0]);
			 e->setOperand(op);
			 (yyval)=e;}
#line 2617 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 498 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTUnaryExpr *e = new ASTExprNegate((yylsp[-1]));
			   ASTExpr *op = (ASTExpr *)(yyvsp[0]);
			   e->setOperand(op);
			   (yyval)=e;}
#line 2626 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 502 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTUnaryExpr *e = new ASTExprBitNot((yylsp[-1]));
					ASTExpr *op = (ASTExpr *)(yyvsp[0]);
					e->setOperand(op);
					(yyval)=e;}
#line 2635 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 506 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 2641 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 509 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval)=(yyvsp[-1]);}
#line 2647 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 510 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2653 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 511 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTUnaryExpr *e = new ASTExprIncrement((yylsp[0]));
						 ASTExpr *op = (ASTExpr *)(yyvsp[-1]);
						 e->setOperand(op);
						 (yyval)=e;}
#line 2662 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 515 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTUnaryExpr *e = new ASTExprPreIncrement((yylsp[-1]));
						 ASTExpr *op = (ASTExpr *)(yyvsp[0]);
						 e->setOperand(op);
						 (yyval)=e;}
#line 2671 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 519 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTUnaryExpr *e = new ASTExprDecrement((yylsp[0]));
						 ASTExpr *op = (ASTExpr *)(yyvsp[-1]);
						 e->setOperand(op);
						 (yyval)=e;}
#line 2680 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 523 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTUnaryExpr *e = new ASTExprPreDecrement((yylsp[-1]));
						 ASTExpr *op = (ASTExpr *)(yyvsp[0]);
						 e->setOperand(op);
						 (yyval)=e;}
#line 2689 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 527 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTFloat *val = (ASTFloat *)(yyvsp[0]);
		    (yyval) = new ASTNumConstant(val,(yylsp[0]));}
#line 2696 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 529 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTString *as = (ASTString *)(yyvsp[0]);
			char val[15];
			sprintf(val, "%d", as->getValue().at(1));
			(yyval) = new ASTNumConstant(new ASTFloat(val,0,(yylsp[0])),(yylsp[0]));}
#line 2705 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 533 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = (yyvsp[0]);}
#line 2711 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 534 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval)=(yyvsp[0]);}
#line 2717 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 537 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTBoolConstant(true,(yylsp[0]));}
#line 2723 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 538 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTBoolConstant(false,(yylsp[0]));}
#line 2729 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 541 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTFuncCall *fc = (ASTFuncCall *)(yyvsp[-1]);
							    ASTExpr *name = (ASTExpr *)(yyvsp[-3]);
							    fc->setName(name);
							    (yyval)=fc;}
#line 2738 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 545 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTFuncCall *fc = new ASTFuncCall((yylsp[-2]));
					    ASTExpr *name = (ASTExpr *)(yyvsp[-2]);
					    fc->setName(name);
					    (yyval)=fc;}
#line 2747 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 551 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTFuncCall *fc = (ASTFuncCall *)(yyvsp[0]);
					  ASTExpr *e = (ASTExpr *)(yyvsp[-2]);
					  fc->addParam(e);
					  (yyval) = fc;}
#line 2756 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 555 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTFuncCall *fc = new ASTFuncCall((yylsp[0]));
		  ASTExpr *e = (ASTExpr *)(yyvsp[0]);
		  fc->addParam(e);
		  (yyval) = fc;}
#line 2765 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 561 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTStmt *prec = (ASTStmt *)(yyvsp[-6]);
												ASTExpr *term = (ASTExpr *)(yyvsp[-4]);
												ASTStmt *incr = (ASTExpr *)(yyvsp[-2]);
												ASTStmt *stmt = (ASTStmt *)(yyvsp[0]);
												(yyval) = new ASTStmtFor(prec,term,incr,stmt,(yylsp[-8]));}
#line 2775 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 568 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTExpr *cond = (ASTExpr *)(yyvsp[-2]);
										   ASTStmt *stmt = (ASTStmt *)(yyvsp[0]);
										   (yyval) = new ASTStmtWhile(cond,stmt,(yylsp[-4]));}
#line 2783 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 572 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTExpr *cond = (ASTExpr *)(yyvsp[-1]);
										   ASTStmt *stmt = (ASTStmt *)(yyvsp[-4]);
										   (yyval) = new ASTStmtDo(cond,stmt,(yylsp[-5]));}
#line 2791 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 576 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTExpr *cond = (ASTExpr *)(yyvsp[-2]);
							  ASTStmt *stmt = (ASTStmt *)(yyvsp[0]);
							  (yyval) = new ASTStmtIf(cond,stmt,(yylsp[-4]));}
#line 2799 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 579 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {ASTExpr *cond = (ASTExpr *)(yyvsp[-4]);
										ASTStmt *ifstmt = (ASTStmt *)(yyvsp[-2]);
										ASTStmt *elsestmt = (ASTStmt *)(yyvsp[0]);
										(yyval) = new ASTStmtIfElse(cond,ifstmt,elsestmt,(yylsp[-6]));}
#line 2808 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 585 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTStmtReturnVal((ASTExpr *)(yyvsp[0]),(yylsp[-1]));}
#line 2814 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 586 "src/parser/ffscript.ypp" /* yacc.c:1646  */
    {(yyval) = new ASTStmtReturn((yylsp[0]));}
#line 2820 "src/parser/y.tab.cpp" /* yacc.c:1646  */
    break;


#line 2824 "src/parser/y.tab.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 589 "src/parser/ffscript.ypp" /* yacc.c:1906  */


/*        programs */

void yyerror(const char *s) {
	char temp[512];
    snprintf(temp, 512, "line %d: %s, on token %s", yylineno, s, yytext);
    box_out(temp);
    box_eol();
}

int go(const char *f)
{
yyin = NULL;
resetLexer();
yyin = fopen(f, "r");
if(!yyin)
{
	box_out("Can't open input file");
	box_eol();
	return -1;
}
	curfilename = string(f);
	int result = yyparse();
	fclose(yyin);
	return result;
}
/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 1 "estelar.y"
#include <assert.h>
#line 2 "estelar.y"
#include <vector>
#line 3 "estelar.y"
#include <list>
#line 5 "estelar.y"
#include "Module.h"
#line 6 "estelar.y"
#include "FunctionNode.h"
#line 7 "estelar.y"
#include "Assignment.h"
#line 8 "estelar.y"
#include "Statement.h"
#line 9 "estelar.y"
#include "FunctionCall.h"
#line 10 "estelar.y"
#include "If.h"
#line 11 "estelar.y"
#include "Closure.h"
#line 12 "estelar.y"
#include "Atom.h"
#line 13 "estelar.y"
#include "Ref.h"
#line 14 "estelar.y"
#include "WeakRef.h"
#line 34 "estelar.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    ParseTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 61
#define YYACTIONTYPE unsigned char
#define ParseTOKENTYPE est::Token *
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  est::Constant * yy5;
  est::Closure * yy16;
  est::Assignment * yy17;
  std::list<est::Decl *> * yy34;
  std::list<est::Parm *> * yy46;
  est::Module * yy65;
  est::Atom * yy72;
  est::Statement * yy73;
  est::Decl * yy75;
  std::list<est::Statement*> * yy79;
  std::list<est::Node*> * yy80;
  est::Node * yy93;
  est::Parm * yy95;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 103
#define YYNRULE 58
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    61,   21,   97,    4,   73,    2,  120,   98,   26,   18,
 /*    10 */    17,   59,   15,  100,   78,   38,   74,   73,   23,   14,
 /*    20 */   102,   60,   72,   64,   35,   64,   97,    7,   73,   61,
 /*    30 */    21,   98,    1,   69,   70,   71,   68,    3,   78,   37,
 /*    40 */    74,   15,   25,   20,   26,   18,   17,   23,   14,  101,
 /*    50 */    60,   72,   96,   94,   82,   89,    7,   92,   33,   30,
 /*    60 */    99,   32,   69,   70,   71,   68,   63,  103,   88,   77,
 /*    70 */    57,   16,   22,   11,   10,    9,   12,   25,   20,   26,
 /*    80 */    18,   17,   61,   21,   63,   24,   62,   24,   29,   58,
 /*    90 */    36,    5,   28,   80,   15,   25,   20,   26,   18,   17,
 /*   100 */    23,   14,   27,   60,   72,  162,   56,   75,   67,   53,
 /*   110 */   163,   73,  163,    8,   98,   69,   70,   71,   68,   61,
 /*   120 */    21,   78,   42,   74,  163,  163,  163,  163,  163,  163,
 /*   130 */    97,   15,   73,   34,   63,   98,  163,   23,   14,  163,
 /*   140 */    60,   72,   78,   45,   74,   25,   20,   26,   18,   17,
 /*   150 */    93,   95,   69,   70,   71,   68,   84,  163,  127,   44,
 /*   160 */   163,   73,  163,  163,   98,   90,  163,  163,   65,   91,
 /*   170 */   163,   66,   42,   74,   86,  163,  163,   44,  163,   73,
 /*   180 */   163,  163,   98,   90,  163,  163,   65,   91,  163,   66,
 /*   190 */    42,   74,  163,  163,  163,   76,  163,  163,   44,  163,
 /*   200 */    73,  163,  163,   98,   90,  163,  163,   65,   91,  163,
 /*   210 */    66,   42,   74,  163,   31,  163,  163,   44,  163,   73,
 /*   220 */   163,  163,   98,   90,  163,  163,   65,   91,  163,   66,
 /*   230 */    42,   74,   44,  163,   73,   34,  129,   98,   90,  163,
 /*   240 */   163,   65,   85,  163,   66,   42,   74,  129,  129,  129,
 /*   250 */   129,  129,   93,   95,   93,   95,   97,    6,   73,  163,
 /*   260 */    97,   98,   73,   19,   13,   98,  163,  163,   78,   51,
 /*   270 */    74,  163,   78,   55,   74,   97,  163,   73,  163,  163,
 /*   280 */    98,  163,  163,  163,  163,  163,  163,   78,   81,   74,
 /*   290 */    97,  163,   73,  163,   97,   98,   73,  163,  163,   98,
 /*   300 */   163,  163,   78,   41,   74,  163,   78,   50,   74,  163,
 /*   310 */   163,   97,  163,   73,  163,   97,   98,   73,   60,  163,
 /*   320 */    98,  163,  163,   78,   48,   74,  163,   78,   49,   74,
 /*   330 */    69,   70,   71,   39,  163,   73,  163,  163,   98,  163,
 /*   340 */   163,  163,  163,  163,  163,   78,   42,   74,   97,  163,
 /*   350 */    73,  163,   97,   98,   73,  163,  163,   98,  163,  163,
 /*   360 */    78,   43,   74,  163,   78,   47,   74,  163,  163,   97,
 /*   370 */   163,   73,  163,   97,   98,   73,  163,  163,   98,  163,
 /*   380 */   163,   78,   79,   74,  163,   78,   54,   74,  163,  163,
 /*   390 */   163,   97,  163,   73,  163,  163,   98,  163,  163,  163,
 /*   400 */   163,  163,  163,   78,   52,   74,   97,  163,   73,  163,
 /*   410 */    40,   98,   73,  163,  163,   98,  163,  163,   78,   87,
 /*   420 */    74,  163,   78,   42,   74,  163,  163,   97,  163,   73,
 /*   430 */   163,   97,   98,   73,  163,  163,   98,  163,  163,   78,
 /*   440 */    83,   74,  163,   78,   46,   74,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,    2,   45,    3,   47,    3,   27,   50,   14,   15,
 /*    10 */    16,   23,   13,   56,   57,   58,   59,   47,   19,   20,
 /*    20 */    50,   22,   23,   23,   25,   23,   45,   28,   47,    1,
 /*    30 */     2,   50,   29,   34,   35,   36,   37,   56,   57,   58,
 /*    40 */    59,   13,   12,   13,   14,   15,   16,   19,   20,   44,
 /*    50 */    22,   23,   48,   49,   26,    3,   28,    3,    2,   40,
 /*    60 */    53,    2,   34,   35,   36,   37,    1,    0,   27,   23,
 /*    70 */    43,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*    80 */    15,   16,    1,    2,    1,   33,    3,   33,   40,   22,
 /*    90 */     2,   41,   39,   23,   13,   12,   13,   14,   15,   16,
 /*   100 */    19,   20,   24,   22,   23,   52,   43,   23,   37,   45,
 /*   110 */    60,   47,   60,   32,   50,   34,   35,   36,   37,    1,
 /*   120 */     2,   57,   58,   59,   60,   60,   60,   60,   60,   60,
 /*   130 */    45,   13,   47,    2,    1,   50,   60,   19,   20,   60,
 /*   140 */    22,   23,   57,   58,   59,   12,   13,   14,   15,   16,
 /*   150 */    19,   20,   34,   35,   36,   37,   42,   60,   27,   45,
 /*   160 */    60,   47,   60,   60,   50,   51,   60,   60,   54,   55,
 /*   170 */    60,   57,   58,   59,   42,   60,   60,   45,   60,   47,
 /*   180 */    60,   60,   50,   51,   60,   60,   54,   55,   60,   57,
 /*   190 */    58,   59,   60,   60,   60,   42,   60,   60,   45,   60,
 /*   200 */    47,   60,   60,   50,   51,   60,   60,   54,   55,   60,
 /*   210 */    57,   58,   59,   60,   42,   60,   60,   45,   60,   47,
 /*   220 */    60,   60,   50,   51,   60,   60,   54,   55,   60,   57,
 /*   230 */    58,   59,   45,   60,   47,    2,    1,   50,   51,   60,
 /*   240 */    60,   54,   55,   60,   57,   58,   59,   12,   13,   14,
 /*   250 */    15,   16,   19,   20,   19,   20,   45,   24,   47,   60,
 /*   260 */    45,   50,   47,   30,   31,   50,   60,   60,   57,   58,
 /*   270 */    59,   60,   57,   58,   59,   45,   60,   47,   60,   60,
 /*   280 */    50,   60,   60,   60,   60,   60,   60,   57,   58,   59,
 /*   290 */    45,   60,   47,   60,   45,   50,   47,   60,   60,   50,
 /*   300 */    60,   60,   57,   58,   59,   60,   57,   58,   59,   60,
 /*   310 */    60,   45,   60,   47,   60,   45,   50,   47,   22,   60,
 /*   320 */    50,   60,   60,   57,   58,   59,   60,   57,   58,   59,
 /*   330 */    34,   35,   36,   45,   60,   47,   60,   60,   50,   60,
 /*   340 */    60,   60,   60,   60,   60,   57,   58,   59,   45,   60,
 /*   350 */    47,   60,   45,   50,   47,   60,   60,   50,   60,   60,
 /*   360 */    57,   58,   59,   60,   57,   58,   59,   60,   60,   45,
 /*   370 */    60,   47,   60,   45,   50,   47,   60,   60,   50,   60,
 /*   380 */    60,   57,   58,   59,   60,   57,   58,   59,   60,   60,
 /*   390 */    60,   45,   60,   47,   60,   60,   50,   60,   60,   60,
 /*   400 */    60,   60,   60,   57,   58,   59,   45,   60,   47,   60,
 /*   410 */    45,   50,   47,   60,   60,   50,   60,   60,   57,   58,
 /*   420 */    59,   60,   57,   58,   59,   60,   60,   45,   60,   47,
 /*   430 */    60,   45,   50,   47,   60,   60,   50,   60,   60,   57,
 /*   440 */    58,   59,   60,   57,   58,   59,
};
#define YY_SHIFT_USE_DFLT (-22)
#define YY_SHIFT_MAX 68
static const short yy_shift_ofst[] = {
 /*     0 */   -22,   -1,   -1,   -1,   -1,   28,   81,  118,  118,  118,
 /*    10 */   118,  118,  118,  118,  118,  118,  118,  118,  118,  118,
 /*    20 */   118,  118,  118,  118,  118,  118,  118,  296,   67,    0,
 /*    30 */     2,    3,  -22,  -22,  -22,  -22,  -22,   65,   65,  235,
 /*    40 */   235,   83,  133,  133,  233,  133,  133,   30,   30,   30,
 /*    50 */    30,   30,   30,  131,   -6,   -6,   54,   52,  -12,   56,
 /*    60 */    59,   46,   88,   70,   78,   41,  -21,   84,   71,
};
#define YY_REDUCE_USE_DFLT (-44)
#define YY_REDUCE_MAX 36
static const short yy_reduce_ofst[] = {
 /*     0 */    53,  132,  153,  172,  114,  187,  -43,  -19,   64,  211,
 /*    10 */   249,  307,  346,  303,  365,  324,  270,  230,  382,   85,
 /*    20 */   215,  245,  266,  288,  386,  328,  361,  -30,    4,    7,
 /*    30 */     7,    5,   19,   48,   63,   50,   27,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   105,  161,  161,  161,  161,  161,  161,  161,  161,  161,
 /*    10 */   161,  161,  161,  161,  161,  161,  161,  161,  161,  161,
 /*    20 */   161,  161,  161,  161,  161,  161,  161,  161,  161,  161,
 /*    30 */   161,  122,  110,  110,  146,  116,  146,  161,  124,  141,
 /*    40 */   139,  161,  161,  126,  129,  125,  145,  147,  152,  151,
 /*    50 */   148,  149,  150,  129,  131,  132,  161,  161,  161,  161,
 /*    60 */   161,  161,  130,  161,  111,  161,  137,  161,  161,  154,
 /*    70 */   155,  156,  157,  153,  142,  158,  108,  160,  137,  136,
 /*    80 */   159,  135,  113,  134,  107,  115,  121,  133,  117,  143,
 /*    90 */   118,  114,  144,  140,  106,  138,  104,  129,  128,  109,
 /*   100 */   123,  119,  112,
};
#define YY_SZ_ACTTAB (int)(sizeof(yy_action)/sizeof(yy_action[0]))

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  ParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "DOT",           "LP",            "RP",          
  "AND",           "OR",            "EQ",            "NE",          
  "GT",            "GE",            "LT",            "LE",          
  "PLUS",          "MINUS",         "TIMES",         "DIVIDE",      
  "MOD",           "EXP",           "NOT",           "PLUSPLUS",    
  "MINUSMINUS",    "ATOM",          "FUNCTION",      "ID",          
  "EQUALS",        "LBRACE",        "RBRACE",        "SEMICOLON",   
  "IF",            "ELSE",          "PLUSEQUALS",    "MINUSEQUALS", 
  "AMPER",         "COMMA",         "INT",           "STRING",      
  "FLOAT",         "COLON",         "error",         "decl_list",   
  "parm_list",     "stmt_list",     "stmt_block",    "expr_list",   
  "else",          "atom",          "rhs",           "lambda",      
  "decl",          "function",      "constant",      "assignment",  
  "module",        "parm",          "stmt",          "formal_stmt", 
  "bool_expr",     "expr_stmt",     "expr",          "function_call",
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "module ::= decl_list",
 /*   1 */ "decl_list ::= decl_list decl",
 /*   2 */ "decl_list ::=",
 /*   3 */ "decl ::= function",
 /*   4 */ "function ::= FUNCTION ID LP parm_list RP stmt_block",
 /*   5 */ "lambda ::= FUNCTION LP parm_list RP stmt_block",
 /*   6 */ "parm_list ::= parm_list parm",
 /*   7 */ "parm_list ::=",
 /*   8 */ "parm ::= ID",
 /*   9 */ "parm ::= ID EQUALS constant",
 /*  10 */ "stmt_block ::= LBRACE stmt_list RBRACE",
 /*  11 */ "stmt_block ::= formal_stmt",
 /*  12 */ "stmt_list ::= stmt_list formal_stmt",
 /*  13 */ "stmt_list ::=",
 /*  14 */ "formal_stmt ::= stmt SEMICOLON",
 /*  15 */ "stmt ::= assignment",
 /*  16 */ "stmt ::= IF bool_expr stmt_block else",
 /*  17 */ "stmt ::= expr_stmt",
 /*  18 */ "else ::= ELSE stmt_block",
 /*  19 */ "else ::=",
 /*  20 */ "assignment ::= atom EQUALS bool_expr",
 /*  21 */ "assignment ::= atom EQUALS expr",
 /*  22 */ "assignment ::= atom PLUSEQUALS expr",
 /*  23 */ "assignment ::= atom MINUSEQUALS expr",
 /*  24 */ "assignment ::= atom EQUALS AMPER atom",
 /*  25 */ "expr ::= constant",
 /*  26 */ "expr ::= atom",
 /*  27 */ "expr ::= LP expr RP",
 /*  28 */ "expr ::= expr PLUS expr",
 /*  29 */ "expr ::= expr MINUS expr",
 /*  30 */ "expr ::= expr TIMES expr",
 /*  31 */ "expr ::= expr DIVIDE expr",
 /*  32 */ "expr ::= expr MOD expr",
 /*  33 */ "expr ::= MINUS expr",
 /*  34 */ "expr ::= expr_stmt",
 /*  35 */ "expr_stmt ::= atom MINUSMINUS",
 /*  36 */ "expr_stmt ::= MINUSMINUS atom",
 /*  37 */ "expr_stmt ::= atom PLUSPLUS",
 /*  38 */ "expr_stmt ::= PLUSPLUS atom",
 /*  39 */ "expr_stmt ::= function_call",
 /*  40 */ "function_call ::= LP expr RP LP expr_list RP",
 /*  41 */ "function_call ::= atom LP expr_list RP",
 /*  42 */ "expr_list ::= expr_list COMMA expr",
 /*  43 */ "expr_list ::=",
 /*  44 */ "bool_expr ::= expr GT expr",
 /*  45 */ "bool_expr ::= expr GE expr",
 /*  46 */ "bool_expr ::= expr LT expr",
 /*  47 */ "bool_expr ::= expr LE expr",
 /*  48 */ "bool_expr ::= expr EQ expr",
 /*  49 */ "bool_expr ::= expr NE expr",
 /*  50 */ "constant ::= lambda",
 /*  51 */ "constant ::= INT",
 /*  52 */ "constant ::= STRING",
 /*  53 */ "constant ::= FLOAT",
 /*  54 */ "atom ::= ID",
 /*  55 */ "atom ::= COLON COLON ID",
 /*  56 */ "atom ::= expr DOT ID",
 /*  57 */ "atom ::= DOT ID",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    case 39: /* decl_list */
{
#line 43 "estelar.y"
 delete (yypminor->yy34); 
#line 562 "estelar.c"
}
      break;
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from ParseAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_MAX || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        return yy_find_shift_action(pParser, iFallback);
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( j>=0 && j<YY_SZ_ACTTAB && yy_lookahead[j]==YYWILDCARD ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_MAX ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_MAX );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_SZ_ACTTAB );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   ParseARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
   ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 52, 1 },
  { 39, 2 },
  { 39, 0 },
  { 48, 1 },
  { 49, 6 },
  { 47, 5 },
  { 40, 2 },
  { 40, 0 },
  { 53, 1 },
  { 53, 3 },
  { 42, 3 },
  { 42, 1 },
  { 41, 2 },
  { 41, 0 },
  { 55, 2 },
  { 54, 1 },
  { 54, 4 },
  { 54, 1 },
  { 44, 2 },
  { 44, 0 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 3 },
  { 51, 4 },
  { 58, 1 },
  { 58, 1 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 3 },
  { 58, 2 },
  { 58, 1 },
  { 57, 2 },
  { 57, 2 },
  { 57, 2 },
  { 57, 2 },
  { 57, 1 },
  { 59, 6 },
  { 59, 4 },
  { 43, 3 },
  { 43, 0 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 56, 3 },
  { 50, 1 },
  { 50, 1 },
  { 50, 1 },
  { 50, 1 },
  { 45, 1 },
  { 45, 3 },
  { 45, 3 },
  { 45, 2 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
  yygotominor = yyzerominor;


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 0: /* module ::= decl_list */
#line 70 "estelar.y"
{ yygotominor.yy65 = new est::Module(yymsp[0].minor.yy34); }
#line 906 "estelar.c"
        break;
      case 1: /* decl_list ::= decl_list decl */
#line 72 "estelar.y"
{ yygotominor.yy34 = yymsp[-1].minor.yy34; yygotominor.yy34->push_back(yymsp[0].minor.yy75); }
#line 911 "estelar.c"
        break;
      case 2: /* decl_list ::= */
#line 73 "estelar.y"
{ yygotominor.yy34 = new std::list<est::Decl *>(); }
#line 916 "estelar.c"
        break;
      case 3: /* decl ::= function */
#line 75 "estelar.y"
{ yygotominor.yy75 = yymsp[0].minor.yy75; }
#line 921 "estelar.c"
        break;
      case 4: /* function ::= FUNCTION ID LP parm_list RP stmt_block */
#line 80 "estelar.y"
{ 
	yygotominor.yy75 = new est::Decl(yymsp[-4].minor.yy0, new est::Closure(yymsp[-2].minor.yy46, yymsp[0].minor.yy79));
}
#line 928 "estelar.c"
        break;
      case 5: /* lambda ::= FUNCTION LP parm_list RP stmt_block */
#line 85 "estelar.y"
{ 
	yygotominor.yy16 = new est::Closure(yymsp[-2].minor.yy46, yymsp[0].minor.yy79);
}
#line 935 "estelar.c"
        break;
      case 6: /* parm_list ::= parm_list parm */
#line 89 "estelar.y"
{ yygotominor.yy46 = yymsp[-1].minor.yy46; yygotominor.yy46->push_back(yymsp[0].minor.yy95); }
#line 940 "estelar.c"
        break;
      case 7: /* parm_list ::= */
#line 90 "estelar.y"
{ yygotominor.yy46 = new std::list<est::Parm *>(); }
#line 945 "estelar.c"
        break;
      case 8: /* parm ::= ID */
#line 92 "estelar.y"
{ yygotominor.yy95 = new est::Parm(yymsp[0].minor.yy0); }
#line 950 "estelar.c"
        break;
      case 9: /* parm ::= ID EQUALS constant */
#line 93 "estelar.y"
{ yygotominor.yy95 = new est::Parm(yymsp[-2].minor.yy0, yymsp[0].minor.yy5); }
#line 955 "estelar.c"
        break;
      case 10: /* stmt_block ::= LBRACE stmt_list RBRACE */
#line 95 "estelar.y"
{ yygotominor.yy79 = yymsp[-1].minor.yy79; }
#line 960 "estelar.c"
        break;
      case 11: /* stmt_block ::= formal_stmt */
#line 96 "estelar.y"
{ yygotominor.yy79 = new std::list<est::Statement *>(); yygotominor.yy79->push_back(yymsp[0].minor.yy73); }
#line 965 "estelar.c"
        break;
      case 12: /* stmt_list ::= stmt_list formal_stmt */
#line 98 "estelar.y"
{ yygotominor.yy79 = yymsp[-1].minor.yy79; yygotominor.yy79->push_back(yymsp[0].minor.yy73); }
#line 970 "estelar.c"
        break;
      case 13: /* stmt_list ::= */
#line 99 "estelar.y"
{ yygotominor.yy79 = new std::list<est::Statement *>(); }
#line 975 "estelar.c"
        break;
      case 14: /* formal_stmt ::= stmt SEMICOLON */
#line 101 "estelar.y"
{ yygotominor.yy73 = yymsp[-1].minor.yy73; }
#line 980 "estelar.c"
        break;
      case 15: /* stmt ::= assignment */
#line 103 "estelar.y"
{ yygotominor.yy73 = yymsp[0].minor.yy17; }
#line 985 "estelar.c"
        break;
      case 16: /* stmt ::= IF bool_expr stmt_block else */
#line 105 "estelar.y"
{ 
	yygotominor.yy73 = new est::If(yymsp[-2].minor.yy93, yymsp[-1].minor.yy79, yymsp[0].minor.yy79, yymsp[-3].minor.yy0->lineno); 
}
#line 992 "estelar.c"
        break;
      case 17: /* stmt ::= expr_stmt */
#line 109 "estelar.y"
{ yygotominor.yy73 = new est::Statement(yymsp[0].minor.yy93);}
#line 997 "estelar.c"
        break;
      case 18: /* else ::= ELSE stmt_block */
#line 111 "estelar.y"
{ yygotominor.yy79 = yymsp[0].minor.yy79; }
#line 1002 "estelar.c"
        break;
      case 19: /* else ::= */
#line 112 "estelar.y"
{ yygotominor.yy79 = NULL; }
#line 1007 "estelar.c"
        break;
      case 20: /* assignment ::= atom EQUALS bool_expr */
      case 21: /* assignment ::= atom EQUALS expr */ yytestcase(yyruleno==21);
#line 117 "estelar.y"
{ yygotominor.yy17 = new est::Assignment(yymsp[-2].minor.yy72, yymsp[0].minor.yy93); }
#line 1013 "estelar.c"
        break;
      case 22: /* assignment ::= atom PLUSEQUALS expr */
#line 120 "estelar.y"
{ yygotominor.yy17 = new est::AssignmentPlus(yymsp[-2].minor.yy72, yymsp[0].minor.yy93); }
#line 1018 "estelar.c"
        break;
      case 23: /* assignment ::= atom MINUSEQUALS expr */
#line 121 "estelar.y"
{ yygotominor.yy17 = new est::AssignmentMinus(yymsp[-2].minor.yy72, yymsp[0].minor.yy93); }
#line 1023 "estelar.c"
        break;
      case 24: /* assignment ::= atom EQUALS AMPER atom */
#line 122 "estelar.y"
{ yygotominor.yy17 = new est::Assignment(yymsp[-3].minor.yy72, new est::Ref(yymsp[0].minor.yy72)); }
#line 1028 "estelar.c"
        break;
      case 25: /* expr ::= constant */
#line 132 "estelar.y"
{ yygotominor.yy93 = new est::ValueNode(yymsp[0].minor.yy5); }
#line 1033 "estelar.c"
        break;
      case 26: /* expr ::= atom */
#line 133 "estelar.y"
{ yygotominor.yy93 = new est::ValueNode(yymsp[0].minor.yy72); }
#line 1038 "estelar.c"
        break;
      case 27: /* expr ::= LP expr RP */
#line 134 "estelar.y"
{ yygotominor.yy93 = yymsp[-1].minor.yy93; }
#line 1043 "estelar.c"
        break;
      case 28: /* expr ::= expr PLUS expr */
#line 135 "estelar.y"
{ yygotominor.yy93 = new est::Plus(yymsp[-2].minor.yy93, yymsp[0].minor.yy93, yymsp[-1].minor.yy0->lineno); }
#line 1048 "estelar.c"
        break;
      case 29: /* expr ::= expr MINUS expr */
#line 136 "estelar.y"
{ yygotominor.yy93 = new est::Minus(yymsp[-2].minor.yy93, yymsp[0].minor.yy93, yymsp[-1].minor.yy0->lineno); }
#line 1053 "estelar.c"
        break;
      case 30: /* expr ::= expr TIMES expr */
#line 137 "estelar.y"
{ yygotominor.yy93 = new est::Times(yymsp[-2].minor.yy93, yymsp[0].minor.yy93, yymsp[-1].minor.yy0->lineno); }
#line 1058 "estelar.c"
        break;
      case 31: /* expr ::= expr DIVIDE expr */
#line 138 "estelar.y"
{ yygotominor.yy93 = new est::Divide(yymsp[-2].minor.yy93, yymsp[0].minor.yy93, yymsp[-1].minor.yy0->lineno); }
#line 1063 "estelar.c"
        break;
      case 32: /* expr ::= expr MOD expr */
#line 139 "estelar.y"
{ yygotominor.yy93 = new est::Mod(yymsp[-2].minor.yy93, yymsp[0].minor.yy93, yymsp[-1].minor.yy0->lineno); }
#line 1068 "estelar.c"
        break;
      case 38: /* expr_stmt ::= PLUSPLUS atom */
#line 146 "estelar.y"
{ yygotominor.yy93 = new est::PrePlusPlus(yymsp[0].minor.yy72); }
#line 1073 "estelar.c"
        break;
      case 39: /* expr_stmt ::= function_call */
#line 147 "estelar.y"
{ yygotominor.yy93 = yymsp[0].minor.yy93; }
#line 1078 "estelar.c"
        break;
      case 40: /* function_call ::= LP expr RP LP expr_list RP */
#line 150 "estelar.y"
{ 
	yygotominor.yy93 = new est::FunctionCall(yymsp[-4].minor.yy93, yymsp[-1].minor.yy80); 
}
#line 1085 "estelar.c"
        break;
      case 41: /* function_call ::= atom LP expr_list RP */
#line 154 "estelar.y"
{ yygotominor.yy93 = new est::FunctionCall(yymsp[-3].minor.yy72, yymsp[-1].minor.yy80); }
#line 1090 "estelar.c"
        break;
      case 42: /* expr_list ::= expr_list COMMA expr */
#line 156 "estelar.y"
{ yygotominor.yy80 = yymsp[-2].minor.yy80; yygotominor.yy80->push_back(yymsp[0].minor.yy93); }
#line 1095 "estelar.c"
        break;
      case 43: /* expr_list ::= */
#line 157 "estelar.y"
{ yygotominor.yy80 = new std::list<est::Node *>(); }
#line 1100 "estelar.c"
        break;
      case 44: /* bool_expr ::= expr GT expr */
      case 45: /* bool_expr ::= expr GE expr */ yytestcase(yyruleno==45);
      case 46: /* bool_expr ::= expr LT expr */ yytestcase(yyruleno==46);
      case 47: /* bool_expr ::= expr LE expr */ yytestcase(yyruleno==47);
      case 48: /* bool_expr ::= expr EQ expr */ yytestcase(yyruleno==48);
      case 49: /* bool_expr ::= expr NE expr */ yytestcase(yyruleno==49);
#line 159 "estelar.y"
{ yygotominor.yy93 = new est::GT(yymsp[-2].minor.yy93, yymsp[0].minor.yy93, yymsp[-1].minor.yy0->lineno); }
#line 1110 "estelar.c"
        break;
      case 50: /* constant ::= lambda */
#line 166 "estelar.y"
{ yygotominor.yy5 = yymsp[0].minor.yy16; }
#line 1115 "estelar.c"
        break;
      case 51: /* constant ::= INT */
#line 167 "estelar.y"
{ yygotominor.yy5 = new est::IntConstant(yymsp[0].minor.yy0); }
#line 1120 "estelar.c"
        break;
      case 52: /* constant ::= STRING */
#line 168 "estelar.y"
{ yygotominor.yy5 = new est::StringConstant(yymsp[0].minor.yy0); }
#line 1125 "estelar.c"
        break;
      case 53: /* constant ::= FLOAT */
#line 169 "estelar.y"
{ yygotominor.yy5 = new est::FloatConstant(yymsp[0].minor.yy0); }
#line 1130 "estelar.c"
        break;
      default:
      /* (33) expr ::= MINUS expr */ yytestcase(yyruleno==33);
      /* (34) expr ::= expr_stmt */ yytestcase(yyruleno==34);
      /* (35) expr_stmt ::= atom MINUSMINUS */ yytestcase(yyruleno==35);
      /* (36) expr_stmt ::= MINUSMINUS atom */ yytestcase(yyruleno==36);
      /* (37) expr_stmt ::= atom PLUSPLUS */ yytestcase(yyruleno==37);
      /* (54) atom ::= ID */ yytestcase(yyruleno==54);
      /* (55) atom ::= COLON COLON ID */ yytestcase(yyruleno==55);
      /* (56) atom ::= expr DOT ID */ yytestcase(yyruleno==56);
      /* (57) atom ::= DOT ID */ yytestcase(yyruleno==57);
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  ParseARG_FETCH;
#define TOKEN (yyminor.yy0)
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  ParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor,yyminorunion);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}

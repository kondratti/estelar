%include {#include <assert.h>}
%include {#include <vector>}
%include {#include <list>}

%include {#include "Module.h"}
%include {#include "FunctionNode.h"}
%include {#include "Assignment.h"}
%include {#include "Statement.h"}
%include {#include "FunctionCall.h"}
%include {#include "If.h"}
%include {#include "Closure.h"}
%include {#include "Atom.h"}
%include {#include "Ref.h"}
%include {#include "WeakRef.h"}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

%right DOT.
%right LP RP.
%left AND.
%left OR.
%left EQ NE GT GE LT LE.
%left PLUS MINUS.
%left TIMES DIVIDE MOD.
%right EXP NOT.
%right PLUSPLUS MINUSMINUS.
%right ATOM.

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

%token_type {est::Token *}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//%type sourcefile {est::DeclList*}
//%destructor sourcefile  { abc($$);}

%default_type		{est::Node *}

%type decl_list		{std::list<est::Decl *> *}
%destructor decl_list { delete $$; }
%type parm_list		{std::list<est::Parm *> *}
%type stmt_list		{std::list<est::Statement*> *}
%type stmt_block	{std::list<est::Statement*> *}
%type expr_list		{std::list<est::Node*> *}
%type else			{std::list<est::Statement*> *}

%type atom			{est::Atom *}
%type rhs			{est::Node *}
%type lambda		{est::Closure *}
%type decl			{est::Decl *}
%type function		{est::Decl *}
%type constant		{est::Constant *}
%type assignment	{est::Assignment *}
%type module		{est::Module *}
%type parm			{est::Parm *}
%type stmt			{est::Statement *}
%type formal_stmt	{est::Statement *}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

%token_prefix EST_

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

module(M)		::= decl_list(B).					{ M = new est::Module(B); }

decl_list(L)	::= decl_list(L2) decl(D). 			{ L = L2; L->push_back(D); }
decl_list(L)	::= .								{ L = new std::list<est::Decl *>(); }

decl(A)			::= function(B).					{ A = B; }
//decl(A)			::= ID(I) EQUALS expr.					
//decl(A)			::= ID(I) EQUALS bool_expr.					

function(F)		::= FUNCTION ID(I) LP parm_list(PL) RP stmt_block(SB). 
{ 
	F = new est::Decl(I, new est::Closure(PL, SB));
}

lambda(F)		::= FUNCTION LP parm_list(PL) RP stmt_block(SB). 
{ 
	F = new est::Closure(PL, SB);
}

parm_list(L)	::= parm_list(L2) parm(P). 			{ L = L2; L->push_back(P); }
parm_list(L)	::= .								{ L = new std::list<est::Parm *>(); }

parm(P)			::= ID(I).							{ P = new est::Parm(I); }
parm(P)			::= ID(I) EQUALS constant(C).		{ P = new est::Parm(I, C); }

stmt_block(B)	::= LBRACE stmt_list(L) RBRACE.		{ B = L; }
stmt_block(B)	::= formal_stmt(S).					{ B = new std::list<est::Statement *>(); B->push_back(S); }

stmt_list(L)	::= stmt_list(M) formal_stmt(S).	{ L = M; L->push_back(S); }
stmt_list(L)	::= .								{ L = new std::list<est::Statement *>(); }

formal_stmt(F)	::= stmt(S) SEMICOLON.				{ F = S; }

stmt(S)			::= assignment(A).					{ S = A; }
stmt(S)			::= IF(I) bool_expr(E) stmt_block(B) else(E2).	
{ 
	S = new est::If(E, B, E2, I->lineno); 
}
//stmt(S)			::= rhs(E).							{ S = new est::Statement(E); }
stmt(S)			::= expr_stmt(E).					{ S = new est::Statement(E);}

else(E)			::= ELSE stmt_block(B).				{ E = B; }
else(E)			::= .								{ E = NULL; }

//assignment(A) ::= atom(I) EQUALS expr(N).			{ A = new est::Assignment(I, N); }
//assignment(A) ::= atom(I) EQUALS bool_expr(N).	{ A = new est::Assignment(I, N); }

assignment(A)	::= atom(I) EQUALS bool_expr(N).	{ A = new est::Assignment(I, N); }
//assignment(A)	::= atom(I) EQUALS constant(C).		{ A = new est::Assignment(I, C); }
assignment(A)	::= atom(I) EQUALS expr(N).			{ A = new est::Assignment(I, N); }
assignment(A)	::= atom(I) PLUSEQUALS expr(N).		{ A = new est::AssignmentPlus(I, N); }
assignment(A)	::= atom(I) MINUSEQUALS expr(N).	{ A = new est::AssignmentMinus(I, N); }
assignment(A)	::= atom(I) EQUALS AMPER atom(A2).	{ A = new est::Assignment(I, new est::Ref(A2)); }

//rhs(R)			::= bool_expr(B).					{ R = B; R->syntaxType(BOOL);}
//rhs(R)			::= expr(E).						{ R = E; R->syntaxType(EXPR);}
//rhs(R)			::= AMPER atom(A).					{ R = new est::Ref(A); R->syntaxType(REF); }

//rhs(R) ::= atom(A).								{ R = new est::WeakRef(A); }
//rhs ::= constant. 
//rhs(R) ::= lambda(C).								{ R = new est::ValueNode(C); }

expr(E)			::= constant(C).					{ E = new est::ValueNode(C); }
expr(E)			::= atom(A). [ATOM]					{ E = new est::ValueNode(A); }
expr(E)			::= LP expr(E2) RP.					{ E = E2; }
expr(E)			::= expr(E1) PLUS(OP) expr(E2).		{ E = new est::Plus(E1, E2, OP->lineno); }
expr(E)			::= expr(E1) MINUS(OP) expr(E2).	{ E = new est::Minus(E1, E2, OP->lineno); }
expr(E)			::= expr(E1) TIMES(OP) expr(E2).	{ E = new est::Times(E1, E2, OP->lineno); }
expr(E)			::= expr(E1) DIVIDE(OP) expr(E2).	{ E = new est::Divide(E1, E2, OP->lineno); }
expr(E)			::= expr(E1) MOD(OP) expr(E2).		{ E = new est::Mod(E1, E2, OP->lineno); }
expr			::= MINUS expr.	[NOT]
expr			::= expr_stmt.

expr_stmt		::= atom MINUSMINUS.
expr_stmt		::= MINUSMINUS atom.
expr_stmt		::= atom PLUSPLUS.
expr_stmt(E)	::= PLUSPLUS atom(A).				{ E = new est::PrePlusPlus(A); }
expr_stmt(E)	::= function_call(F).				{ E = F; }

function_call(F) ::= LP expr(E1) RP LP expr_list(E) RP.	
{ 
	F = new est::FunctionCall(E1, E); 
}

function_call(X) ::= atom(E1) LP expr_list(E) RP.	{ X = new est::FunctionCall(E1, E); }

expr_list(L)	::= expr_list(L2) COMMA expr(E).	{ L = L2; L->push_back(E); }
expr_list(L)	::= .								{ L = new std::list<est::Node *>(); }

bool_expr(E)	::= expr(E1) GT(OP) expr(E2).		{ E = new est::GT(E1, E2, OP->lineno); }
bool_expr(E)	::= expr(E1) GE(OP) expr(E2).		{ E = new est::GT(E1, E2, OP->lineno); }
bool_expr(E)	::= expr(E1) LT(OP) expr(E2).		{ E = new est::GT(E1, E2, OP->lineno); }
bool_expr(E)	::= expr(E1) LE(OP) expr(E2).		{ E = new est::GT(E1, E2, OP->lineno); }
bool_expr(E)	::= expr(E1) EQ(OP) expr(E2).		{ E = new est::GT(E1, E2, OP->lineno); }
bool_expr(E)	::= expr(E1) NE(OP) expr(E2).		{ E = new est::GT(E1, E2, OP->lineno); }

constant(C)		::= lambda(L).						{ C = L; }
constant(C)		::= INT(V).							{ C = new est::IntConstant(V); }
constant(C)		::= STRING(V).						{ C = new est::StringConstant(V); }
constant(C)		::= FLOAT(V).						{ C = new est::FloatConstant(V); }

//constant(C) ::= TRUE(V).							{ C = new est::FloatConstant(V); }
//constant(C) ::= FALSE(V).							{ C = new est::FloatConstant(V); }

//var_declare ::= LOCAL ID.
//var_declare ::= GLOBAL ID.

atom			::= ID.
atom			::= COLON COLON ID.
atom			::= expr DOT ID.
atom			::= DOT ID.

//atom ::= table DOT ID.
//atom ::= LP expr RP DOT ID.
//table ::= expr.
%{
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "scanType.h"
#include "ast.h"
#include "exp.h"
#include "var.h"
#include "fun.h"
#include "stmt.h"
#include "yyerror.h"
#include "parser.tab.h"

#define YYERROR_VERBOSE

extern int yylex();
extern FILE *yyin;
extern int yylineno;
extern char *yytext;
extern AST *tree;

extern void yyerror(const char *);
%}

%locations

%union {
	TokenData *tokenData;
	AST *ast;
}

%token <tokenData> BOOLCONST NUMCONST CHARCONST STRINGCONST ID
%token <tokenData> IF WHILE FOR STATIC INT BOOL CHAR IN ELSE RETURN BREAK
%token <tokenData> EQ ADDASS SUBASS DIVASS MULASS LEQ GEQ NEQ DEC INC
%token <tokenData> ADD SUB LT GT MUL DIV MOD RAND ASS AND OR NOT ACCESS
%start declarationList

%type <ast> declarationList declaration varDeclaration scopedVarDeclaration varDeclList varDeclInitialize varDeclId
%type <ast> funDeclaration params paramList paramTypeList paramIdList paramId statement matched unmatched expressionStmt
%type <ast> compoundStmt localDeclarations statementList matchedSelectionStmt unmatchedSelectionStmt matchedIterationStmt
%type <ast> unmatchedIterationStmt returnStmt breakStmt expression simpleExpression andExpression unaryRelExpression
%type <ast> relExpression sumExpression mulExpression unaryExpression factor mutable immutable call args argList
%type <tokenData> constant typeSpecifier relop unaryop mulop sumop

%%
/*

structure

*/
declarationList : declarationList declaration
	{
		tree->append($2);
	}
	| declaration
	{
		tree->append($1);
		if($1 != NULL)
			$1->isFirst = true;
	}
	;
declaration : varDeclaration
	{
		$$ = $1;
	}
	| funDeclaration
	{
		$$ = $1;
	}
	| error
	{
		$$ = NULL;
	}
	;
/*

variables

*/
varDeclaration : typeSpecifier varDeclList ';'
	{
		$$ = $2;
		((Var *)$$)->setTypeAndStatic($1->tokenString, false);
		((Var *)$$)->setInitialized();
		yyerrok;
	}
	| error varDeclList ';'
	{
		$$ = NULL;
	}
	| typeSpecifier error ';'
	{
		$$ = NULL;
		yyerrok;
	}
	;
scopedVarDeclaration : STATIC typeSpecifier varDeclList ';'
	{
		$$ = $3;
		((Var *)$$)->setTypeAndStatic($2->tokenString, true);
		((Var *)$$)->setInitialized();
		yyerrok;
	}
	| typeSpecifier varDeclList ';'
	{
		$$ = $2;
		((Var *)$$)->setTypeAndStatic($1->tokenString, false);
		yyerrok;
	}
	| error varDeclList ';'
	{
		$$ = NULL;
		yyerrok;
	}
	;
varDeclList : varDeclList ',' varDeclInitialize
	{
		$$->append($3);
		yyerrok;
	}
	| varDeclList ',' error
	{
		$$ = NULL;
	}
	| error
	{
		$$ = NULL;
	}
	| varDeclInitialize
	{
		$$ = $1;
	}
	;
varDeclInitialize : varDeclId
	{
		$$ = $1;
	}
	| varDeclId ':' simpleExpression
	{
		$$ = $1;
		((Var *)$$)->initialized = true;
		$$->addChild($3, 0);
	}
	| error ':' simpleExpression
	{
		$$ = NULL;
		yyerrok;
	}
	| varDeclId ':' error
	{
		$$ = NULL;
	}
	;
varDeclId : ID
	{
		$$ = new Var($1);
	}
	| ID ACCESS NUMCONST ']'
	{
		$$ = new Var($1, $3);
	}
	| ID ACCESS error
	{
		$$ = NULL;
	}
	| error ']'
	{
		$$ = NULL;
		yyerrok;
	}
	;
typeSpecifier : INT
	{
		$$ = $1;
	}
	| BOOL
	{
		$$ = $1;
	}
	| CHAR
	{
		$$ = $1;
	}
	;
/*

functions

*/
funDeclaration : typeSpecifier ID '(' params ')' statement
	{
		$$ = new FunDeclaration($1, $2, $4, $6);
	}
	| ID '(' params ')' statement
	{
		$$ = new FunDeclaration($1, $3, $5);
	}
	| typeSpecifier error
	{
		$$ = NULL;
	}
	| typeSpecifier ID '(' error
	{
		$$ = NULL;
	}
	| typeSpecifier ID '(' params ')' error
	{
		$$ = NULL;
	}
	| ID '(' error
	{
		$$ = NULL;
	}
	| ID '(' params ')' error
	{
		$$ = NULL;
	}
	;
params : paramList
	{
		$$ = $1;
	}
    | /* empty */
	{
		$$ = NULL;
	}
	;
paramList : paramList ';' paramTypeList
	{
		$$->append($3);
	}
	| paramTypeList
	{
		$$ = $1;
	}
	| paramList ';' error
	{
		$$ = NULL;
	}
	| error
	{
		$$ = NULL;
	}
	;
paramTypeList : typeSpecifier paramIdList
	{
		$$ = $2;
		((Var *)$$)->setTypeAndStatic($1->tokenString, false);
	}
	| typeSpecifier error
	{
		$$ = NULL;
	}
	;
paramIdList : paramIdList ',' paramId
	{
		$$->append($3);
		yyerrok;
	}
	| paramId
	{
		$$ = $1;
	}
	| paramIdList ',' error
	{
		$$ = NULL;
	}
	| error
	{
		$$ = NULL;
	}
	;
paramId : ID
	{
		$$ = new Par($1, false);
	}
	| ID ACCESS ']'
	{
		$$ = new Par($1, true);
	}
	| error ']'
	{
		$$ = NULL;
		yyerrok;
	}
	;
/*

	statements

*/
statement : matched
	{
		$$ = $1;
	}
	| unmatched
	{
		$$ = $1;
	}
	;
matched : expressionStmt
	{
		$$ = $1;
	}
	| compoundStmt
	{
		$$ = $1;
	}
	| matchedSelectionStmt
	{
		$$ = $1;
	}
	| matchedIterationStmt
	{
		$$ = $1;
	}
	| returnStmt
	{
		$$ = $1;
	}
	| breakStmt
	{
		$$ = $1;
	}
	| IF error
	{
		$$ = NULL;
	}
	| IF error ELSE matched
	{
		$$ = NULL;
		yyerrok;
	}
	| IF error ')' matched ELSE matched
	{
		$$ = NULL;
		yyerrok;
	}
	| WHILE error ')' matched
	{
		$$ = NULL;
		yyerrok;
	}
	| WHILE error
	{
		$$ = NULL;
	}
	| FOR error ')' matched
	{
		$$ = NULL;
		yyerrok;
	}
	| FOR error
	{
		$$ = NULL;
	}
	;
unmatched : unmatchedSelectionStmt
	{
		$$ = $1;
	}
	| unmatchedIterationStmt
	{
		$$ = $1;
	}
	| IF error ')' statement
	{
		$$ = NULL;
		yyerrok;
	}
	| IF error ELSE unmatched
	{
		$$ = NULL;
		yyerrok;
	}
	| IF error ')' matched ELSE unmatched
	{
		$$ = NULL;
		yyerrok;
	}
	| WHILE error ')' unmatched
	{
		$$ = NULL;
		yyerrok;
	}
	| FOR error ')' unmatched
	{
		$$ = NULL;
		yyerrok;
	}
	;
expressionStmt : expression ';'
	{
		$$ = $1;
		yyerrok;
	}
	| ';'
	{
		$$ = NULL;
		yyerrok;
	}
	| error ';'
	{
		$$ = NULL;
		yyerrok;
	}
	;
compoundStmt : '{' localDeclarations statementList '}'
	{
		$$ = new CompoundStatement(@1.first_line, $2, $3);
	}
	| '{' localDeclarations error '}'
	{
		$$ = NULL;
		yyerrok;
	}
	| '{' error statementList '}'
	{
		$$ = NULL;
		yyerrok;
	}
	;
localDeclarations : localDeclarations scopedVarDeclaration
	{
		$$->append($2);
	}
	| /* empty */
	{
		$$ = new AST();
	}
	;
statementList : statementList statement
	{
		$$->append($2);
	}
	| /* empty */
	{
		$$ = new AST();
	}
	;
matchedSelectionStmt : IF '(' simpleExpression ')' matched ELSE matched
	{
		$$ = new If(@1.first_line, $3, $5, $7);
	}
	;
unmatchedSelectionStmt : IF '(' simpleExpression ')' statement
	{
		$$ = new If(@1.first_line, $3, $5);
	}
	| IF '(' simpleExpression ')' matched ELSE unmatched
	{
		$$ = new If(@1.first_line, $3, $5, $7);
	}
	;
matchedIterationStmt : WHILE '(' simpleExpression ')' matched
	{
		$$ = new While(@1.first_line, $3, $5);
	}
	| FOR '(' ID IN ID ')' matched
	{
		$$ = new For(@1.first_line, $3, $5, $7);
	}
	;
unmatchedIterationStmt : WHILE '(' simpleExpression ')' unmatched
	{
		$$ = new While(@1.first_line, $3, $5);
	}
	| FOR '(' ID IN ID ')' unmatched
	{
		$$ = new For(@1.first_line, $3, $5, $7);
	}
	;
returnStmt : RETURN ';'
	{
		$$ = new Return(@1.first_line);
	}
	| RETURN expression ';'
	{
		$$ = new Return(@1.first_line, $2);
		yyerrok;
	}
	;
breakStmt : BREAK ';'
	{
		$$ = new Break(@1.first_line);
	}
	;
/*

expressions

*/
expression : mutable ASS expression
	{
		$$ = new Assignment($2, $1, $3);
	}
	| mutable ADDASS expression
	{
		$$ = new Assignment($2, $1, $3);
	}
	| mutable SUBASS expression
	{
		$$ = new Assignment($2, $1, $3);
	}
	| mutable MULASS expression
	{
		$$ = new Assignment($2, $1, $3);
	}
	| mutable DIVASS expression
	{
		$$ = new Assignment($2, $1, $3);
	}
	| mutable INC
	{
		$$ = new ShortcutAssignment($2, $1);
	}
	| mutable DEC
	{
		$$ = new ShortcutAssignment($2, $1);
	}
	| simpleExpression
	{
		$$ = $1;
	}
	| error INC
	{
		$$ = NULL;
		yyerrok;
	}
	| error DEC
	{
		$$ = NULL;
		yyerrok;
	}
	| error ASS error
	{
		$$ = NULL;
	}
	| error ADDASS error
	{
		$$ = NULL;
	}
	| error SUBASS error
	{
		$$ = NULL;
	}
	| error MULASS error
	{
		$$ = NULL;
	}
	| error DIVASS error
	{
		$$ = NULL;
	}
	;
simpleExpression : simpleExpression OR andExpression
	{
		$$ = new Operation($2, $1, $3);
	}
	| andExpression
	{
		$$ = $1;
	}
	| simpleExpression OR error
	{
		$$ = NULL;
	}
	;
andExpression : andExpression AND unaryRelExpression
	{
		$$ = new Operation($2, $1, $3);
	}
	| unaryRelExpression
	{
		$$ = $1;
	}
	| andExpression AND error
	{
		$$ = NULL;
	}
	;
unaryRelExpression : NOT unaryRelExpression
	{
		$$ = new Operation($1, $2);
	}
	| relExpression
	{
		$$ = $1;
	}
	| NOT error
	{
		$$ = NULL;
	}
	;
relExpression : sumExpression relop sumExpression
	{
		$$ = new Operation($2, $1, $3);
	}
	| sumExpression
	{
		$$ = $1;
	}
	| sumExpression relop error
	{
		$$ = NULL;
	}
	;
relop : LEQ
	{
		$$ = $1;
	}
    | LT
	{
		$$ = $1;
	}
    | GT
	{
		$$ = $1;
	}
    | GEQ
	{
		$$ = $1;
	}
    | EQ
	{
		$$ = $1;
	}
    | NEQ
	{
		$$ = $1;
	}
	;
sumExpression : sumExpression sumop mulExpression
	{
		$$ = new Operation($2, $1, $3);
	}
	| mulExpression
	{
		$$ = $1;
	}
	| sumExpression sumop error
	{
		$$ = NULL;
		yyerrok;
	}
	;
sumop : ADD
	{
		$$ = $1;
	}
    | SUB
	{
		$$ = $1;
	}
	;
mulExpression : mulExpression mulop unaryExpression
	{
		$$ = new Operation($2, $1, $3);
	}
	| unaryExpression
	{
		$$ = $1;
	}
	| mulExpression mulop error
	{
		$$ = NULL;
	}
	;
mulop : MUL
	{
		$$ = $1;
	}
    | DIV
	{
		$$ = $1;
	}
    | MOD
	{
		$$ = $1;
	}
	;
unaryExpression : unaryop unaryExpression
	{
		$$ = new Operation($1, $2);
	}
	| factor
	{
		$$ = $1;
	}
	| unaryop error
	{
		$$ = NULL;
	}
	;
unaryop : SUB
	{
		$$ = $1;
	}
	| MUL
	{
		$$ = $1;
	}
	| RAND
	{
		$$ = $1;
	}
	;
factor : immutable
	{
		$$ = $1;
	}
    | mutable
	{
		$$ = $1;
	}
	;
mutable : ID
	{
		$$ = new Id($1);
	}
	| ID ACCESS expression ']'
	{
		$$ = new Operation($2, new Id($1), $3);
	}
	;
immutable : '(' expression ')'
	{
		$$ = $2;
		yyerrok;
	}
	| call
	{
		$$ = $1;
	}
	| constant
	{
		$$ = new Constant($1);
	}
	| '(' error
	{
		$$ = NULL;
	}
	| error ')'
	{
		$$ = NULL;
		yyerrok;
	}
	;
call : ID '(' args ')'
	{
		$$ = new Call($1, $3);
	}
	| error '('
	{
		$$ = NULL;
		yyerrok;
	}
	;
args : argList
	{
		$$ = $1;
	}
    | /* empty */
	{
		$$ = NULL;
	}
	;
argList : argList ',' expression
	{
		$$->append($3);
		yyerrok;
	}
	| expression
	{
		$$ = $1;
	}
	| argList ',' error
	{
		$$ = NULL;
	}
	;
constant : NUMCONST
	{
		$$ = $1;
	}
	| CHARCONST
	{
		$$ = $1;
	}
	| STRINGCONST
	{
		$$ = $1;
	}
	| BOOLCONST
	{
		$$ = $1;
	}
	;
%%
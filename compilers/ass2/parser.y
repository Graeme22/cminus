%{
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "ourgetopt.h"
#include "scanType.h"
#include "ast.h"
#include "exp.h"
#include "var.h"
#include "fun.h"
#include "stmt.h"
#include "parser.tab.h"

extern int yylex();
extern FILE *yyin;
extern int yylineno;
extern char *yytext;

void yyerror(const char *msg) {
	printf("Error: %s while parsing `%s` on line %d.\n", msg, yytext, yylineno);
}

AST *tree;
%}

%locations

%union {
	TokenData *tokenData;
	AST *ast;
}

%token <tokenData> BOOLCONST NUMCONST CHARCONST STRINGCONST ID
%token <tokenData> IF WHILE FOR STATIC INT BOOL CHAR IN ELSE RETURN BREAK
%token <tokenData> EQ ADDASS SUBASS DIVASS MULASS LEQ GEQ NEQ DEC INC
%token <tokenData> ADD SUB LT GT MUL DIV MOD RAND ASS AND OR NOT
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
		$1->setFirst();
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
	;
/*

variables

*/
varDeclaration : typeSpecifier varDeclList ';'
	{
		$$ = $2;
		((Var *)$$)->setTypeAndStatic($1->tokenString, false);
	}
	;
scopedVarDeclaration : STATIC typeSpecifier varDeclList ';'
	{
		$$ = $3;
		((Var *)$$)->setTypeAndStatic($2->tokenString, true);
	}
	| typeSpecifier varDeclList ';'
	{
		$$ = $2;
		((Var *)$$)->setTypeAndStatic($1->tokenString, false);
	}
	;
varDeclList : varDeclList ',' varDeclInitialize
	{
		$$->append($3);
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
		$$->children[0] = $3;
	}
	;
varDeclId : ID
	{
		$$ = new Var($1);
	}
	| ID '[' NUMCONST ']'
	{
		$$ = new Var($1, $3);
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
	;
paramTypeList : typeSpecifier paramIdList
	{
		$$ = $2;
		((Par *)$$)->setType($1->tokenString);
	}
	;
paramIdList : paramIdList ',' paramId
	{
		$$->append($3);
	}
	| paramId
	{
		$$ = $1;
	}
	;
paramId : ID
	{
		$$ = new Par($1, false);
	}
	| ID '[' ']'
	{
		$$ = new Par($1, true);
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
	;
unmatched : unmatchedSelectionStmt
	{
		$$ = $1;
	}
	| unmatchedIterationStmt
	{
		$$ = $1;
	}
	;
expressionStmt : expression ';'
	{
		$$ = $1;
	}
	| ';'
	{
		$$ = NULL;
	}
	;
compoundStmt : '{' localDeclarations statementList '}'
	{
		$$ = new CompoundStatement(@1.first_line, $2, $3);
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
		$$ = new Operation($2, $1, $3);
	}
	| mutable ADDASS expression
	{
		$$ = new Operation($2, $1, $3);
	}
	| mutable SUBASS expression
	{
		$$ = new Operation($2, $1, $3);
	}
	| mutable MULASS expression
	{
		$$ = new Operation($2, $1, $3);
	}
	| mutable DIVASS expression
	{
		$$ = new Operation($2, $1, $3);
	}
	| mutable INC
	{
		$$ = new Operation($2, $1);
	}
	| mutable DEC
	{
		$$ = new Operation($2, $1);
	}
	| simpleExpression
	{
		$$ = $1;
	}
	;
simpleExpression : simpleExpression OR andExpression
	{
		$$ = new LogicExpression($2, $1, $3);
	}
	| andExpression
	{
		$$ = $1;
	}
	;
andExpression : andExpression AND unaryRelExpression
	{
		$$ = new LogicExpression($2, $1, $3);
	}
	| unaryRelExpression
	{
		$$ = $1;
	}
	;
unaryRelExpression : NOT unaryRelExpression
	{
		$$ = new LogicExpression($1, $2);
	}
	| relExpression
	{
		$$ = $1;
	}
	;
relExpression : sumExpression relop sumExpression
	{
		$$ = new Relation($2, $1, $3);
	}
	| sumExpression
	{
		$$ = $1;
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
		$$ = new VarAccess($1);
	}
	| mutable '[' expression ']'
	{
		$$ = new VarAccess(@2.first_line, $1, $3);
	}
	;
immutable : '(' expression ')'
	{
		$$ = $2;
	}
	| call
	{
		$$ = $1;
	}
	| constant
	{
		$$ = new Constant($1);
	}
	;
call : ID '(' args ')'
	{
		$$ = new Call($1, $3);
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
	}
	| expression
	{
		$$ = $1;
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

int main(int argc, char *argv[]) {
	tree = new AST();

	// -d: turn on yydebug
	// -p: print parse tree
	int dflag = 0, pflag = 0;
	int c;

	while((c = ourGetopt(argc, argv, (char *)"dp")) != -1) {
		switch(c) {
		case 'd':
			dflag = 1;
			break;
		case 'p':
			pflag = 1;
			break;
		case '?':
			fprintf(stderr, "usage: c- [-d] [-p] file\n");
			return -1;
		}
	}

	if(dflag)
		yydebug = 1;

	if(optind < argc) {
		yyin = fopen(argv[optind], "r");
		yyparse();
		fclose(yyin);
	} else
		yyparse();

	tree->propagateInfo();

	if(pflag)
		tree->print();

	return 0;
}

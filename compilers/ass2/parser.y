%{
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "ourgetopt.h"
#include "scanType.h"
#include "ast.h"
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

%union {
	TokenData *tokenData;
	AST *ast;
}

%token <tokenData> BOOLCONST NUMCONST CHARCONST STRINGCONST ID
%token <tokenData> IF WHILE FOR STATIC INT BOOL CHAR IN ELSE RETURN BREAK COMMENT
%token <tokenData> EQ ADDASS SUBASS DIVASS MULASS LEQ GEQ NEQ DEC INC
%start declarationList

%type <ast> declarationList declaration varDeclaration scopedVarDeclaration varDeclList varDeclInitialize varDeclId
%type <ast> funDeclaration params paramList paramTypeList paramIdList paramId statement matched unmatched expressionStmt
%type <ast> compoundStmt localDeclarations statementList matchedSelectionStmt unmatchedSelectionStmt matchedIterationStmt
%type <ast> unmatchedIterationStmt returnStmt breakStmt expression simpleExpression andExpression unaryRelExpression
%type <ast> relExpression sumExpression sumop mulExpression mulop unaryExpression unaryop factor
%type <ast> mutable immutable call args argList
%type <tokenData> constant typeSpecifier

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
		$$ = new VarDeclaration($1, $2);
	}
	;
scopedVarDeclaration : STATIC typeSpecifier varDeclList ';'
	{
		$$ = new ScopedVarDeclaration($2, $3, true);
	}
	| typeSpecifier varDeclList ';'
	{
		$$ = new ScopedVarDeclaration($1, $2, false);
	}
	;
varDeclList : varDeclList ',' varDeclInitialize
	{
		$$->append($3);
	}
	| varDeclInitialize
	{
		$$ = new VarList($1);
	}
	;
varDeclInitialize : varDeclId
	{
		$$ = $1;
	}
	| varDeclId ':' simpleExpression
	{
		$$ = $1;
		$$->append($3); // TODO: test this
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
		((Params *)$$)->appendToChild($3);
	}
	| paramTypeList
	{
		$$ = new Params($1);
	}
	;
paramTypeList : typeSpecifier paramIdList
	{
		$$ = $2;
		((ParamList *)$$)->setType($1);
	}
	;
paramIdList : paramIdList ',' paramId
	{
		((ParamList *)$$)->appendToChild($3);
	}
	| paramId
	{
		$$ = new ParamList($1);
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
	  | unmatchedIterationStmt;
expressionStmt : expression ';'
	       | ';';
compoundStmt : '{' localDeclarations statementList '}';
localDeclarations : localDeclarations scopedVarDeclaration
		  | ;
statementList : statementList statement
	      | ;
matchedSelectionStmt : IF '(' simpleExpression ')' matched ELSE matched;
unmatchedSelectionStmt : IF '(' simpleExpression ')' statement
		       | IF '(' simpleExpression ')' matched ELSE unmatched;
matchedIterationStmt : WHILE '(' simpleExpression ')' matched
		     | FOR '(' ID IN ID ')' matched;
unmatchedIterationStmt : WHILE '(' simpleExpression ')' unmatched
		       | FOR '(' ID IN ID ')' unmatched;
returnStmt : RETURN ';'
	   | RETURN expression ';';
breakStmt : BREAK ';';
/*

expressions

*/
expression : mutable '=' expression
	   | mutable ADDASS expression
	   | mutable SUBASS expression
	   | mutable MULASS expression
	   | mutable DIVASS expression
	   | mutable INC
	   | mutable DEC
	   | simpleExpression;
simpleExpression : simpleExpression '|' andExpression
		 | andExpression;
andExpression : andExpression '&' unaryRelExpression
	      | unaryRelExpression;
unaryRelExpression : '!' unaryRelExpression
		   | relExpression;
relExpression : sumExpression relop sumExpression
	      | sumExpression;
relop : LEQ
      | '<'
      | '>'
      | GEQ
      | EQ
      | NEQ;
sumExpression : sumExpression sumop mulExpression
	      | mulExpression;
sumop : '+'
      | '-';
mulExpression : mulExpression mulop unaryExpression
	      | unaryExpression;
mulop : '*'
      | '/'
      | '%';
unaryExpression : unaryop unaryExpression
		| factor;
unaryop : '-'
	| '*'
	| '?';
factor : immutable
       | mutable;
mutable : ID
	| mutable '[' expression ']';
immutable : '(' expression ')'
	  | call
	  | constant;
call : ID '(' args ')';
args : argList
     | ;
argList : argList ',' expression
	| expression;
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

	if(pflag)
		tree->print();

	return 0;
}

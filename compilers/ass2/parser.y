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

TreeNode *tree;
%}

%union {
	ExpType type;
	TokenData *tokenData;
	TreeNode *node;
}

%token <tokenData> BOOLCONST NUMCONST CHARCONST STRINGCONST ID
%token <tokenData> IF WHILE FOR STATIC INT BOOL CHAR IN ELSE RETURN BREAK COMMENT
%token <tokenData> EQ ADDASS SUBASS DIVASS MULASS LEQ GEQ NEQ DEC INC
%start declarationList

%type <node> declarationList declaration varDeclaration scopedVarDeclaration varDeclList varDeclInitialize varDeclId
%type <node> funDeclaration params paramList paramTypeList paramIdList paramId statement matched unmatched expressionStmt
%type <node> compoundStmt localDeclarations statementList matchedSelectionStmt unmatchedSelectionStmt matchedIterationStmt
%type <node> unmatchedIterationStmt returnStmt breakStmt expression simpleExpression andExpression unaryRelExpression
%type <node> relExpression sumExpression sumop mulExpression mulop unaryExpression unaryop factor
%type <node> mutable immutable call args argList

%type <tokenData> typeSpecifier constant

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
		     | typeSpecifier varDeclList ';';
varDeclList : varDeclList ',' varDeclInitialize
	{
		$$->append($3);
	}
	| varDeclInitialize
	{
		$$ = new AST();
		$$->append($1);
	}
	;
varDeclInitialize : varDeclId
	{
		$$ = $1;
	}
	| varDeclId ':' simpleExpression
	{
		$$ = $1; // TODO: make this work
	}
	;
varDeclId : ID
	{
		$$ = $1;
	}
	| ID '[' NUMCONST ']'
	{
		$$ = $1;
		//$$ = new VarDeclId($1, $3->nValue);
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
	       | ID '(' params ')' statement;
params : paramList
       | ;
paramList : paramList ';' paramTypeList
	  | paramTypeList;
paramTypeList : typeSpecifier paramIdList;
paramIdList : paramIdList ',' paramId
	    | paramId;
paramId : ID
	| ID '[' ']';
/*

	statements

*/
statement : matched
	  | unmatched;
matched : expressionStmt
	| compoundStmt
	| matchedSelectionStmt
	| matchedIterationStmt
	| returnStmt
	| breakStmt;
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

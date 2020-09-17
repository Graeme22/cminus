%{
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "ourgetopt.h"
#include "scanType.h"
#include "parser.tab.h"

#ifdef CPLUSPLUS
extern int yylex();
#endif
extern FILE *yyin;
extern int yylineno;
extern char *yytext;

void yyerror(const char *msg) {
	printf("Error: %s while parsing `%s` on line %d.\n", msg, yytext, yylineno);
}

static TreeNode *savedTree;
%}

%union {
	//ExpType type;
	TokenData *tokenData;
	//TreeNode *tree;
}

%token <tokenData> BOOLCONST NUMCONST CHARCONST STRINGCONST ID
%token <tokenData> IF WHILE FOR STATIC INT BOOL CHAR IN ELSE RETURN BREAK COMMENT
%token <tokenData> EQ ADDASS SUBASS DIVASS MULASS LEQ GEQ NEQ DEC INC
%start program

%%
/*

structure

*/
program : declarationList
	{
		savedTree = $1;
	}
	;
declarationList : declarationList declaration
	{
		TreeNode *t = $1;
		if(t != NULL) {
			while(t->sibling != NULL)
				t = t->sibling;
			t->sibling = $2;
			$$ = $1;
		} else
			$$ = $2;
	}
	| declaration
	{
		$$ = $1;
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
		
	}
	;
scopedVarDeclaration : STATIC typeSpecifier varDeclList ';'
		     | typeSpecifier varDeclList ';';
varDeclList : varDeclList ',' varDeclInitialize
	    | varDeclInitialize;
varDeclInitialize : varDeclId
		  | varDeclId ':' simpleExpression;
varDeclId : ID
	  | ID '[' NUMCONST ']';
typeSpecifier : INT
	      | BOOL
	      | CHAR;
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
	 | CHARCONST
	 | STRINGCONST
	 | BOOLCONST;
%%

int main(int argc, char *argv[]) {
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
		printf("p flag found!\n");

	return 0;
}

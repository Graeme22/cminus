%{
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "scanType.h"

#ifdef CPLUSPLUS
extern int yylex();
#endif
extern FILE *yyin;

void yyerror(const char *msg) {
	printf("Error while parsing: %s\n", msg);
}
%}

%union {
	TokenData *tokenData;
}

%token <tokenData> BOOLCONST NUMCONST CHARCONST STRINGCONST ID
%token <tokenData> IF WHILE FOR STATIC INT BOOL CHAR IN ELSE RETURN BREAK COMMENT
%token <tokenData> EQ ADDASS SUBASS DIVASS MULASS LEQ GEQ NEQ DEC INC
%start program

%%
/*

structure

*/
program : declarationList {
	printf("Program syntax is correct!\n");
};
declarationList : declarationList declaration
		| declaration;
declaration : varDeclaration
	    | funDeclaration;
/*

variables

*/
varDeclaration : typeSpecifier varDeclList;
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
statement : expressionStmt
	  | compoundStmt
	  | selectionStmt
	  | iterationStmt
	  | returnStmt
	  | breakStmt;
expressionStmt : expression ';'
	       | ';';
compoundStmt : '{' localDeclarations statementList '}';
localDeclarations : localDeclarations scopedVarDeclaration
		  | ;
statementList : statementList statement
	      | ;
selectionStmt : IF '(' simpleExpression ')' statement
	      | IF '(' simpleExpression ')' statement ELSE statement;
iterationStmt : WHILE '(' simpleExpression ')' statement
	      | FOR '(' ID IN ID ')' statement;
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
	if(argc == 1)
		yyparse();
	else {
		yyin = fopen(argv[1], "r");
		yyparse();
		fclose(yyin);
	}
	return 0;
}

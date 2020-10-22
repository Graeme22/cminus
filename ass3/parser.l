%{
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "scanType.h"
#include "ast.h"
#include "parser.tab.h"

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;

// returns an array of ints.
std::string sValueFrom(char *raw) {
	int len = strlen(raw);
	std::string s;
	int i;
	bool escaped = false;

	for(i = 1; i < len - 1; i++) {
		if(!escaped) {
			if(raw[i] == '\\')
				escaped = true;
			else
				s.append(1, raw[i]);
		} else {
			escaped = false;
			switch(raw[i]) {
			case '0':
				s.append(1, '\0');
				break;
			case 'n':
				s.append(1, '\n');
				break;
			default:
				s.append(1, raw[i]);
			}
		}
	}
	return s;
}

int cValueFrom(char *raw) {
	char c;
	int len = strlen(raw);
	// make sure warning works for escaped first char
	if(raw[1] == '\\') {
		switch(raw[2]) {
		case '0':
			c = '\0';
			break;
		case 'n':
			c = '\n';
			break;
		default:
			c = raw[2];
		}
	} else if(len > 3) {
		printf("WARNING(%d): character is %d characters long and not a single character: '%s'. The first char will be used.\n", yylineno, len - 2, raw);
		if(raw[1] == '\\') {
			switch(raw[2]) {
			case '0':
				c = '\0';
				break;
			case 'n':
				c = '\n';
				break;
			default:
				c = raw[2];
			}
		} else
			c = raw[1];
	} else if(len == 2) {
		printf("ERROR(%d): Empty character ''. Characters ignored.\n", yylineno);
		return -1;
	} else
		c = raw[1];

	return (int)c;
}

static int buildToken(int tokenClass, char *tokenString) {
	yylval.tokenData = new TokenData;
	yylval.tokenData->tokenClass = tokenClass;
	yylval.tokenData->line = yylineno;
	yylval.tokenData->tokenString = strdup(tokenString);

	switch(tokenClass) {
	case NUMCONST:
		yylval.tokenData->nValue = atoi(tokenString);
		break;
	case BOOLCONST:
		yylval.tokenData->nValue = (strcmp(tokenString, "false") == 0 ? 0 : 1);
		break;
	case STRINGCONST:
		yylval.tokenData->sValue = sValueFrom(tokenString);
		break;
	case CHARCONST:
		int c = cValueFrom(tokenString);
		if(c == -1)
			return -1;
		yylval.tokenData->cValue = (char)c;
		break;
	}

	return tokenClass;
}
%}

%option noyywrap
%option yylineno

%%
"if"									{ return buildToken(IF, yytext); }
"while"									{ return buildToken(WHILE, yytext); }
"for"									{ return buildToken(FOR, yytext); }
"static"								{ return buildToken(STATIC, yytext); }
"int"									{ return buildToken(INT, yytext); }
"bool"									{ return buildToken(BOOL, yytext); }
"char"									{ return buildToken(CHAR, yytext); }
"in"									{ return buildToken(IN, yytext); }
"else"									{ return buildToken(ELSE, yytext); }
"return"								{ return buildToken(RETURN, yytext); }
"break"									{ return buildToken(BREAK, yytext); }
"true"|"false"							{ return buildToken(BOOLCONST, yytext); }
"=="									{ return buildToken(EQ, yytext); }
"+="									{ return buildToken(ADDASS, yytext); }
"-="									{ return buildToken(SUBASS, yytext); }
"/="									{ return buildToken(DIVASS, yytext); }
"*="									{ return buildToken(MULASS, yytext); }
"<="									{ return buildToken(LEQ, yytext); }
">="									{ return buildToken(GEQ, yytext); }
"!="									{ return buildToken(NEQ, yytext); }
"--"									{ return buildToken(DEC, yytext); }
"++"									{ return buildToken(INC, yytext); }
"//".*									;
\+										{ return buildToken(ADD, yytext); }
\-										{ return buildToken(SUB, yytext); }
\<										{ return buildToken(LT, yytext); }
\>										{ return buildToken(GT, yytext); }
\*										{ return buildToken(MUL, yytext); }
\/										{ return buildToken(DIV, yytext); }
%										{ return buildToken(MOD, yytext); }
\?										{ return buildToken(RAND, yytext); }
=										{ return buildToken(ASS, yytext); }
&										{ return buildToken(AND, yytext); }
\|										{ return buildToken(OR, yytext); }
!										{ return buildToken(NOT, yytext); }
\[										{ return buildToken(ACCESS, yytext); }
[;,:\]\(\){}]							{ return yytext[0]; }
[a-zA-Z_][a-zA-Z_0-9]*					{ return buildToken(ID, yytext); }
[0-9]+									{ return buildToken(NUMCONST, yytext); }
'([^\n\\']|\\.)*'						{ return buildToken(CHARCONST, yytext); }
\"([^\\\"\n]|\\.)*\"					{ return buildToken(STRINGCONST, yytext); }
[^ \n\t]								{ printf("ERROR(%d): Invalid or misplaced input character: '%c'. Character Ignored.\n", yylineno, yytext[0]); }
.|\n									;
%%

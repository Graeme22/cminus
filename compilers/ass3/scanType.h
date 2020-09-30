#ifndef _SCANTYPE_H_
#define _SCANTYPE_H_

#include <string>
#include <stdbool.h>

struct TokenData {
	int tokenClass;
	char *tokenString;
	int line;

	int nValue;
	char cValue;
	std::string sValue;
};

typedef enum { STMT_K, EXP_K } NodeKind;
typedef enum { EXPRESSION_K, COMPOUND_K, RETURN_K, BREAK_K, SELECTION_K, ITERATION_K } StmtKind;
typedef enum { OP_K, CONST_K, ID_K } ExpKind;
typedef enum { INT_T, BOOL_T, CHAR_T } ExpType;

#endif

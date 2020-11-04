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

#endif

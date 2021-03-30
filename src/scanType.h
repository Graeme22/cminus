#ifndef _SCANTYPE_H_
#define _SCANTYPE_H_

#include <string>
#include <stdbool.h>

struct TokenData {
	// integer representing id, assigned by bison
	int tokenClass;
	// full string of the token
	char *tokenString;
	int line;

	// only one of these will be used at a time depending on
	// the type of the token (numeric, char, or string)
	int nValue;
	char cValue;
	std::string sValue;
};

#endif

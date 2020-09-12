#ifndef _SCANTYPE_H_
#define _SCANTYPE_H_

#include <string>

struct TokenData {
	int tokenClass;
	char *tokenString;
	int line;
	// these may or may not be used depending on the class.
	int nValue;
	char cValue;
	std::string sValue;
};

#endif

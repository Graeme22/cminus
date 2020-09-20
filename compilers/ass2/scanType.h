#ifndef _SCANTYPE_H_
#define _SCANTYPE_H_

#include <string>
#include <stdbool.h>

typedef struct {

	int tokenClass;
	char *tokenString;
	int line;

	union {
		int nValue;
		char cValue;
		std::string sValue;
	};

} TokenData;

#endif

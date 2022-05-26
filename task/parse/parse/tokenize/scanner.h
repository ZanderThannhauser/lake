
#include <stddef.h>

#include "token.h"

struct scanner
{
	int fd;
	
	struct {
		char buffer[4096];
		size_t i, n;
	} chunk;
	
	char c;
	
	enum token token;
	
	struct {
		char* chars;
		size_t n, cap;
	} tokenchars;
};


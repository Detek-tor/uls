#include "../inc/libmx.h"

bool mx_isspace(char c) {
	if (c == 32 || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r') {
		return 1;
	}
	else {
		return 0;
	}
}



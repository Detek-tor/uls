#include "../inc/libmx.h"

char *mx_strtrim(const char *str) {
	int size = 0;

	if (str == NULL) return NULL;
	while (mx_isspace(*str)) {
		str++;
	}
	size = mx_strlen(str);
	
	while (mx_isspace(str[size - 1])) {
		size--;
	}
	char *p = mx_strndup(str, size);
	return p;
}



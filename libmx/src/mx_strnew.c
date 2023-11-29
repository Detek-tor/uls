#include "../inc/libmx.h"

char *mx_strnew(const int size) {
	char *p = NULL;
	int i = 0;
	
	if (size < 0) return NULL;
	p = (char *)malloc((size + 1) * sizeof(char));
	while (i < size) {
		p[i] = '\0';
		i++;
	}
	p[i] = '\0';
	return p;
}



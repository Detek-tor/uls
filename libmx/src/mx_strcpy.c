#include "../inc/libmx.h"

char *mx_strcpy(char *dst, const char *src) {
	int i = 0;
	
	while (src[i] != '\0') {
		i++;
	}
	for (int j = 0; j <= i; j++) {
		dst[j] = src[j];
	}
	return dst;
}



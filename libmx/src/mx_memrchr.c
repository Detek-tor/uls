#include "../inc/libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
	unsigned char *str = (unsigned char *)s;
	unsigned char uc = (unsigned char)c;
	unsigned char *last = str + n - 1;
	
	while (last >= str) {
		if (*last == uc) {
			return last;
		}
		last--;
	}
	return NULL;
}



#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
	unsigned char *str = (unsigned char *)s;
	unsigned char uc = (unsigned char)c;
	size_t length = 0;
	
	while (length < n) {
		if (*str == uc) {
			return str;
		}
		length++;
		str++;
	}
	return NULL;
}



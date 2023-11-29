#include "../inc/libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
	unsigned char *string = (unsigned char *)big;
	unsigned char *part = (unsigned char *)little;
	
	if (little_len > big_len) return NULL;
	if (big_len == 0 || little_len == 0) return NULL;
	
	while (*string++) {
		if (mx_memcmp(string, part, little_len - 1) == 0) {
			return string;
		}
	}
	return NULL;
}

	

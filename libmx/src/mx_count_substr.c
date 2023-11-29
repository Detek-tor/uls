#include "../inc/libmx.h"

int mx_count_substr(const char *str, const char *sub) {
	int len = mx_strlen(sub);
	int i = 0;
	
	if (!str || !sub) return -1;
	if (len == 0) return 0;
	
	while (*str) {
		if (!mx_strncmp((char *)str, (char *)sub, len)) {
			i++;
		}
		str++;
	}
	return i;
}



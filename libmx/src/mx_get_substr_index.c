#include "../inc/libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
	int len_str = mx_strlen(str);
	int len_sub = mx_strlen(sub);
	
	if (str == NULL || sub == NULL) {
		return -2;
	}
	for (int i = 0; i <= len_str - len_sub; i++) {
		if (!mx_strncmp(&str[i], sub, len_sub)) {
			return i;
		}
	}
	
	return -1;
}



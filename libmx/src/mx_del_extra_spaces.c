#include "../inc/libmx.h"

char *mx_del_extra_spaces(const char *str) {
	if (!str) return NULL;
	
	char *p = mx_strnew(mx_strlen(str));
	char *res = NULL;
	int j = 0;
	
	for (int i = 0; str[i]; i++) {
		if (!(mx_isspace(str[i]))) {
			p[j++] = str[i];
		}
		if (!(mx_isspace(str[i])) && mx_isspace(str[i + 1])) {
			p[j++] = ' ';
		}
	}
	
	res = mx_strtrim(p);
	mx_strdel(&p);
	return res;
}

	

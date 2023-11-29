#include "../inc/libmx.h"

char *mx_strdup(const char *s1) {
	char *p = mx_strnew(mx_strlen(s1));
	mx_strcpy(p, s1);
	
	return p;
}



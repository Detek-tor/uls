#include "../inc/libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    	while (*haystack) {
    		const char *h = haystack;
    		const char *n = needle;
    		
    		while (*h == *n && *n) {
    			n++;
    			h++;
    		}
    		if (*n == '\0') {
    			return (char *)haystack;
    		}
    		haystack++;
    	}
    	return NULL;
}



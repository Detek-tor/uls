#include "../inc/libmx.h"

static int letters(const char *s, char c) {
	int i = 0;

	while (s[i] != c && s[i]) {
		i++;
	}
	return i;
}

char **mx_strsplit(const char *s, char c) {
	int length = 0;
	int k = 0;

	if (!s) return NULL;

	char **arr = (char **)malloc((mx_count_words(s, c) + 1) * sizeof(char *));
	while ((*s) && (*s != '\0')) {
		if (*s != c) {
			length = letters(s, c);
			arr[k] = mx_strndup(s, length);
			s += length;
			k++;
			continue;
		}
		s++;
	}
	arr[k] = NULL;
	return arr;
}

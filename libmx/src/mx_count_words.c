#include "../inc/libmx.h"

int mx_count_words(const char *str, char c) {
	int del = 0;
	int word = 0;
	
	if (!str) return -1;
	
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == c) {
			del = 0;
		}
		else if (del == 0) {
			word++;
			del = 1;
		}
	}
	return word;
}



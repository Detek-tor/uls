#include "../inc/libmx.h"

static int num_len(int number) {
	int length = 0;
	
	while (number) {
		number /= 10;
		length++;
	}
	return length;
}

char *mx_itoa(int number) {
	char *str = NULL;
	int length = num_len(number);
	int count = number;
	
	str = mx_strnew(length);
	if (number == -2147483648) {
		return mx_strcpy(str, "-2147483648");
	}
	if (number == 0) {
		return mx_strcpy(str, "0");
	}
	
	for (int i = 0; i < length; i++) {
		if (count < 0) {
			str[length] = '-';
			count = -count;
		}
		str[i] = (count % 10) + '0';
		count /= 10;
	}
	
	int k = mx_strlen(str);
	for (int i = 0; i < k / 2; i++) {
		mx_swap_char(&str[i], &str[k - 1 - i]);
	}
	return str;
}

		

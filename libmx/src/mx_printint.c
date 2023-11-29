#include "../inc/libmx.h"

void mx_printint(int n) {
	char array[50];
	int i = 0;
	
	if (n == -2147483648) {
		write(1, "-2147483648", 11);
	}
	if (n == 0) {
		mx_printchar('0');
	}
	if (n < 0 && n != -2147483648) {
		n *= -1;
		mx_printchar('-');
	}
	while (n != 0 && n != -2147483648) {
		array[i++] = n % 10 + '0';
		n /= 10;
	}
	for (int j = i - 1; j >= 0; j--) {
		mx_printchar(array[j]);
	}
}



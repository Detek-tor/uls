#include "../inc/libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
	unsigned long res = 0;
	int len = 0;
	unsigned long a = 1;
	if (!hex) return 0;
	for (int i = 0; hex[i] != '\0'; i++) {
		len++;
	}
	for (int i = len - 1; i >= 0; i--) {
		if (mx_isdigit(hex[i])) {
			res += (hex[i] - 48) * a;
			a *= 16;
		}
		else if (mx_islower(hex[i])) {
			res += (hex[i] - 87) * a;
			a *= 16;
		}
		else if (mx_isupper(hex[i])) {
			res += (hex[i] - 55) * a;
			a *= 16;
		}
		else if (!mx_isdigit(hex[i]) && !mx_islower(hex[i]) && mx_isupper(hex[i])) {
			return 0;
		}
	}
	return res;
}



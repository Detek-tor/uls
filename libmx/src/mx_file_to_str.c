#include "../inc/libmx.h"

/*char *mx_file_to_str(const char *file) {
	int len = 0;
	char c;
	int string_read = 0;
	
	if (!file) return NULL;
	int f = open(file, O_RDONLY);
	if (f < 0) return NULL;
	
	while (read(f, &c, 1)) {
		len++;
	}
	close(f);
	
	f = open(file, O_RDONLY);
	if (f < 0) return NULL;
	if (len == 0) return NULL;
	
	char *p = mx_strnew(len);
	string_read = read(f, p, len);
	close(f);
	return p;
}*/
char *mx_file_to_str(const char *filename) {
    if (!filename) {
        return NULL;
    }
    int size = 0;
    int i = 0;
    char c;
    int file = open(filename, O_RDONLY);
    if (file < 0)
        return NULL;
    while (read(file, &c, 1))
        size++;
    close(file);
    char *str = mx_strnew(size);
    file = open(filename, O_RDONLY);
    if (file < 0) return NULL;
    while (read(file, &c, 1)) {
        str[i] = c;
        i++;
    }
    close(file);
    return str;
}

	
	

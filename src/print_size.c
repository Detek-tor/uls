#include "../inc/uls.h"

void display_size(off_t size, int width) {
    const char *suf_flags[] = {"B", "K", "M", "G", "T", "P"};
    double size_flags = size;
    int count = 0;

    while (size_flags >= 1000) {
        size_flags /= 1024;
        count++;
    }

    double size_round = round_number(size_flags * 10) / 10;
    char buffer[5] = {'\0'};
    if (size_round >= 10 || count == 0) {
        char *str = mx_ltoa(round_number(size_flags));
        mx_strcat(buffer, str);
        free(str);
    } else {
        char *str = mx_ltoa(size_round);
        mx_strcat(buffer, str);
        free(str);
        mx_strcat(buffer, ".");
        str = mx_ltoa((long long)(size_round * 10) % 10);
        mx_strcat(buffer, str);
        free(str);
    }
    mx_strcat(buffer, suf_flags[count]);
    display_aligned(buffer, width, true);
}

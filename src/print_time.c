#include "../inc/uls.h"

void display_aligned(char *str, int width, bool al_right) {
    int space = width - mx_strlen(str);

    if (!al_right) {
        mx_printstr(str);
    }
    for (int i = 0; i < space; i++) {
        mx_printchar(' ');
    }
    if (al_right) {
        mx_printstr(str);
    }
}

void display_time(time_t p_time, bool f) {
    char *string = ctime(&p_time);
    char **array = mx_strsplit(string, ' ');
    time_t now_time = time(NULL);
    time_t six_months = (365 / 2) * 24 * 60 * 60;

    array[4][4] = '\0';
    if (f) {
        for (int i = 1; array[i] != NULL; i++) {
            display_aligned(array[i], 2, true);
            if (array[i + 1] != NULL) {
                mx_printchar(' ');
            }
        }
    } else if (p_time + six_months <= now_time || p_time >= now_time + six_months) {
        mx_printstr(array[1]);
        mx_printchar(' ');
        display_aligned(array[2], 2, true);
        mx_printstr("  ");
        mx_printstr(array[4]);
    } else {
        mx_printstr(array[1]);
        mx_printchar(' ');
        display_aligned(array[2], 2, true);
        mx_printchar(' ');
        char **array_time = mx_strsplit(array[3], ':');
        mx_printstr(array_time[0]);
        mx_printchar(':');
        mx_printstr(array_time[1]);
        mx_del_strarr(&array_time);
    }
    mx_del_strarr(&array);
}

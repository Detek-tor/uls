#include "../inc/uls.h"

static void display_color(mode_t mode) {
    switch (mode & S_IFMT) {
    case S_IFBLK:
        mx_printstr("\033[34;46m");
        break;
    case S_IFCHR:
        mx_printstr("\033[34;43m");
        break;
    case S_IFDIR:
        if (mode & S_IWOTH) {
            if (mode & S_ISTXT) {
                mx_printstr("\033[30;42m");
            } else {
                mx_printstr("\033[30;43m");
            }
        } else {
            mx_printstr("\033[34m");
        }
        break;
    case S_IFIFO:
        mx_printstr("\033[33m");
        break;
    case S_IFLNK:
        mx_printstr("\033[35m");
        break;
    case S_IFSOCK:
        mx_printstr("\033[32m");
        break;
    default:
        if (mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
            if (mode & S_ISUID) {
                mx_printstr("\033[30;41m");
            } else if (mode & S_ISGID) {
                mx_printstr("\033[30;46m");
            } else {
                mx_printstr("\033[31m");
            }
        }
        break;
    }
}

static int display_classifier(mode_t mode, bool slash_only) {
    char classifier = '\0';

    switch (mode & S_IFMT) {
    case S_IFDIR:
        classifier = '/';
        break;
    case S_IFIFO:
        classifier = '|';
        break;
    case S_IFLNK:
        classifier = '@';
        break;
    case S_IFSOCK:
        classifier = '=';
        break;
    case S_IFREG:
        if (mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
            classifier = '*';
        }
        break;
    }

    if (classifier != '\0') {
        if (slash_only && classifier != '/') {
            return 0;
        }
        mx_printchar(classifier);
        return 1;
    }
    return 0;
}

static char *sub_non_printable(const char *name) {
    char *copy = mx_strdup(name);

    for (int i = 0; copy[i] != '\0'; i++) {
        if (copy[i] >= 0 && copy[i] <= 31) {
            copy[i] = '?';
        }
    }

    return copy;
}

static void display_name(const char *name, bool non_printable) {
    if (non_printable) {
        char *str = sub_non_printable(name);
        mx_printstr(str);
        free(str);
    } else {
        mx_printstr(name);
    }
}

int display_file_info(t_fileInfo *file_info, t_configuration *config) {
    if (config->colorize) {
        display_color(file_info->stat.st_mode);
    }
    /////////////////////
    display_name(file_info->file_name, config->show_non_printable);
    ////////////////////
    if (config->colorize) {
        mx_printstr("\033[0m");
    }

    int count = mx_strlen(file_info->file_name);

    if (config->classify || config->append_slash) {
        count += display_classifier(file_info->stat.st_mode, config->append_slash);
    }
    return count;
}

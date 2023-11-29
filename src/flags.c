#include "../inc/uls.h"

static int handle_print(char flag, t_configuration *settings);
static int handle_format(char flag, t_configuration *settings);
static int handle_sort_and_time(char flag, t_configuration *settings);
static int handle_filter(char flag, t_configuration *settings);

void mx_process_flags(char flag, t_configuration *settings) {
    int count = 0;
    count += handle_format(flag, settings);
    count += handle_print(flag, settings);
    count += handle_sort_and_time(flag, settings);
    count += handle_filter(flag, settings);
    if (count == 4)
    {
        mx_printerr("uls: illegal option -- ");
        write(2, &flag, 1);
        write(2, "\n", 1);
        mx_printerr("usage: uls [-@ACFGRSTacefghlmnopqrtu1] [file ...]\n");
        exit(1);
    }

}

static int handle_format(char flag, t_configuration *settings) {
    switch (flag) {
        case 'l':
            settings->file_format = FORMAT_LONG;
            break;
        case 'C':
            settings->file_format = FORMAT_MULTICOLUMN;
            break;
        case '1':
            settings->file_format = FORMAT_SINGLE_COLUMN;
            break;
        case 'm':
            settings->file_format = FORMAT_STREAM;
            break;
        case 'R':
            settings->recursive = true;
            break;
        default:
            return 1;
    }
    return 0;
}

static int handle_sort_and_time(char flag, t_configuration *settings) {
    switch (flag) {
        case 'r':
            settings->reverse_sort = true;
            break;
        case 'S':
            settings->sort_type = SORT_BY_SIZE;
            break;
        case 't':
            settings->sort_type = SORT_BY_TIME;
            break;
        case 'f':
            settings->sort_type = SORT_NONE;
            settings->ignore_type = IGNORE_NONE;
            break;
        case 'c':
            settings->time_type = TIME_STATUS_CHANGE;
            break;
        case 'u':
            settings->time_type = TIME_ACCESS;
            break;
        default:
            return 1;
    }
    return 0;
}

static int handle_print(char flag, t_configuration *settings) {
    switch (flag) {
        case 'a':
            settings->ignore_type = IGNORE_NONE;
            break;
        case 'A':
            settings->ignore_type = IGNORE_DOTS;
            break;
        case 'F':
            settings->classify = true;
            settings->append_slash = false;
            break;
        case 'p':
            settings->append_slash = true;
            settings->classify = false;
            break;
        case 'G':
            settings->colorize = true;
            break;
        case 'q':
            settings->show_non_printable = true;
            break;
        default:
            return 1;
    }
    return 0;
}

static int handle_filter(char flag, t_configuration *settings) {
    switch (flag) {
        case 'h':
            settings->use_human_readable = true;
            break;
        case 'T':
            settings->complete_time_info = true;
            break;
        case 'g':
            settings->exclude_owner_info = true;
            break;
        case 'o':
            settings->exclude_group_info = true;
            break;
        case 'n':
            settings->display_numeric = true;
            break;
        case 'e':
            settings->include_access_control_list = true;
            break;
        case '@':
            settings->include_extended_attributes = true;
            break;
        default:
            return 1;
    }
    return 0;
}

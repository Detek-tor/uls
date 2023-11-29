#include "../inc/uls.h"

static int maximum_width(t_list *file_info_list) {
    int width = 0;

    while (file_info_list != NULL) {
        t_fileInfo *file_info = file_info_list->data;
        int len = mx_strlen(file_info->file_name);

        if (width < len) {
            width = len;
        }
        file_info_list = file_info_list->next;
    }

    return width;
}

static int retrieve_terminal_width() {
    if (isatty(1)) {
        struct winsize window_size;
        ioctl(0, TIOCGWINSZ, &window_size);
        return window_size.ws_col;
    }
    return 80;
}

static void display_tabs(int width, int tab_width) {
    int tabs = (width + tab_width - 1) / tab_width;

    for (int i = 0; i < tabs; i++) {
        if (tab_width == 1) {
            mx_printchar(' ');
        } else {
            mx_printchar('\t');
        }
    }
}

static t_fileInfo **convert_list_to_array(t_list *file_info_list, int *count) {
    *count = mx_list_size(file_info_list);

    if (*count == 0) {
        return NULL;
    }

    t_fileInfo **array = malloc(sizeof(t_fileInfo *) * (*count));

    for (int i = 0; i < *count; i++) {
        array[i] = file_info_list->data;
        file_info_list = file_info_list->next;
    }

    return array;
}

void display_multicolumn(t_list *file_info_list, t_configuration *config) {
    int tab_width = 8;
    if (config->colorize) {
        tab_width = 1;
    }

    int width = maximum_width(file_info_list);
    if (config->classify || config->append_slash) {
        width++;
    }
    width = (width + tab_width) & ~(tab_width - 1);

    int num_cols = retrieve_terminal_width() / width;
    if (num_cols <= 1) {
        display_single_column(file_info_list, config);
        return;
    }

    int count;
    t_fileInfo **array = convert_list_to_array(file_info_list, &count);
    int num_rows = (count + num_cols - 1) / num_cols;

    int idx = 0;

    for (int i = 0; i < num_rows; i++) {

        idx = i;

        for (int j = 0; j < num_cols; j++) {
            int printed = display_file_info(array[idx], config);
            idx += num_rows;
            if (idx >= count) {
                break;
            }
            display_tabs(width - printed, tab_width);
        }
        mx_printchar('\n');
    }

    if (array != NULL) {
        free(array);
    }
}

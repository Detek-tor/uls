#include "../inc/uls.h"

void display_single_column(t_list *file_info_list, t_configuration *config) {
    while (file_info_list != NULL) {
        display_file_info(file_info_list->data, config);
        mx_printchar('\n');
        file_info_list = file_info_list->next;
    }
}

void display_stream(t_list *file_info_list, t_configuration *config) {
    while (file_info_list != NULL) {
        display_file_info(file_info_list->data, config);
        if (file_info_list->next != NULL) {
            mx_printstr(", ");
        }
        file_info_list = file_info_list->next;
    }
    mx_printchar('\n');
}

void display_file_infos(t_list *file_info_list, t_configuration *config) {
    switch (config->file_format) {
    case FORMAT_SINGLE_COLUMN:
        display_single_column(file_info_list, config);
        break;
    case FORMAT_MULTICOLUMN:
        display_multicolumn(file_info_list, config);
        break;
    case FORMAT_STREAM:
        display_stream(file_info_list, config);
        break;
    case FORMAT_LONG:
        display_long_format(file_info_list, config);
        break;
    default:
        break;
    }
}

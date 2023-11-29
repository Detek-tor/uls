#include "../inc/uls.h"

t_widthInfo calculate_max_width(t_list *file_infos, t_configuration *config) {
    t_widthInfo width = {.num_links = 0, .user_width = 0, .group = 0, .size_width = 0};

    while (file_infos != NULL) {
        t_fileInfo *file_info = file_infos->data;

        char *num_links = mx_ltoa(file_info->stat.st_nlink);
        if (width.num_links < mx_strlen(num_links)) {
            width.num_links = mx_strlen(num_links);
        }
        free(num_links);

        if (width.user_width < mx_strlen(file_info->user_name)) {
            width.user_width = mx_strlen(file_info->user_name);
        }

        if (width.group < mx_strlen(file_info->group_name)) {
            width.group = mx_strlen(file_info->group_name);
        }

        int size_length = 5;
        if (S_ISCHR(file_info->stat.st_mode) || S_ISBLK(file_info->stat.st_mode)) {
            char *hex_size = mx_nbr_to_hex(file_info->stat.st_rdev);
            size_length = mx_strlen(hex_size) + 2;
            free(hex_size);
        } else if (!config->use_human_readable) {
            char *size = mx_ltoa(file_info->stat.st_size);
            size_length = mx_strlen(size);
            free(size);
        }
        if (width.size_width < size_length) {
            width.size_width = size_length;
        }

        file_infos = file_infos->next;
    }

    return width;
}

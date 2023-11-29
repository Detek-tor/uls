#include "../inc/uls.h"

static void display_permissions(mode_t mode) {
    display_filetype(mode);

    mx_printchar((mode & S_IRUSR) ? 'r' : '-');
    mx_printchar((mode & S_IWUSR) ? 'w' : '-');
    mx_printchar((mode & (S_IXUSR)) ? ((mode & S_IXUSR) ? 'x' : 'S') : '-');

    mx_printchar((mode & S_IRGRP) ? 'r' : '-');
    mx_printchar((mode & S_IWGRP) ? 'w' : '-');
    mx_printchar((mode & (S_IXGRP)) ? ((mode & S_IXGRP) ? 'x' : 'S') : '-');

    mx_printchar((mode & S_IROTH) ? 'r' : '-');
    mx_printchar((mode & S_IWOTH) ? 'w' : '-');
    mx_printchar((mode & (S_IXOTH)) ? ((mode & S_IXOTH) ? 'x' : 'T') : '-');
}

static void display_long_aligned(long long number, int width) {
    char *str = mx_ltoa(number);
    display_aligned(str, width, true);
    free(str);
}

static void display_fileinfo_long(t_fileInfo *file_info, t_widthInfo *width, t_configuration *config) {
    display_permissions(file_info->stat.st_mode);

    if (file_info->extended_attr_keys != NULL) {
        mx_printchar('@');
    } else if (file_info->access_control_list != NULL) {
        mx_printchar('+');
    } else {
        mx_printchar(' ');
    }

    mx_printchar(' ');
    display_long_aligned(file_info->stat.st_nlink, width->num_links);
    mx_printchar(' ');

    if (!config->exclude_owner_info) {
        display_aligned(file_info->user_name, width->user_width, false);
        mx_printstr("  ");
    }
    if (!config->exclude_group_info) {
        display_aligned(file_info->group_name, width->group, false);
        mx_printstr("  ");
    }

    if (config->exclude_owner_info && config->exclude_group_info) {
        mx_printstr("  ");
    }

    if (S_ISCHR(file_info->stat.st_mode) || S_ISBLK(file_info->stat.st_mode)) {
        char *hex = mx_nbr_to_hex(file_info->stat.st_rdev);
        char *str;
        if (file_info->stat.st_rdev == 0) {
            str = mx_strdup(hex);
        } else {
            str = mx_strjoin("0x", hex);
        }
        display_aligned(str, width->size_width, true);
        free(str);
        free(hex);
    } else if (config->use_human_readable) {
        display_size(file_info->stat.st_size, width->size_width);
    } else {
        display_long_aligned(file_info->stat.st_size, width->size_width);
    }

    mx_printchar(' ');
    display_time(file_info->timespec.tv_sec, config->complete_time_info);
    mx_printchar(' ');
    display_file_info(file_info, config);
    if (file_info->file_link != NULL) {
        mx_printstr(" -> ");
        mx_printstr(file_info->file_link);
    }
    mx_printchar('\n');

    if (config->include_extended_attributes && file_info->extended_attr_keys != NULL) {
        for (char **ptr = file_info->extended_attr_keys; *ptr != NULL; ptr++) {
            mx_printchar('\t');
            mx_printstr(*ptr);
            mx_printchar('\t');
            ssize_t value_size = getxattr(file_info->file_path, *ptr, NULL, 0, 0, XATTR_NOFOLLOW);
            if (config->use_human_readable) {
                display_size(value_size, 5);
            } else {
                display_long_aligned(value_size, 4);
            }
            mx_printstr(" \n");
        }
    }

    if (config->include_access_control_list && file_info->access_control_list != NULL) {
        char *string = acl_to_text(file_info->access_control_list, NULL);
        char **lines = mx_strsplit(string, '\n');

        for (int i = 1; lines[i] != NULL; i++) {
            mx_printchar(' ');
            mx_printint(i - 1);
            mx_printstr(": ");
            char **parts = mx_strsplit(lines[i], ':');
            mx_printstr(parts[0]);
            mx_printchar(':');
            mx_printstr(parts[2]);
            mx_printchar(' ');
            mx_printstr(parts[4]);
            mx_printchar(' ');
            mx_printstr(parts[5]);
            mx_printchar('\n');
            mx_del_strarr(&parts);
        }
        mx_del_strarr(&lines);
        free(string);
    }
}

void display_long_format(t_list *file_info_list, t_configuration *config) {
    t_widthInfo width = calculate_max_width(file_info_list, config);

    while (file_info_list != NULL) {
        display_fileinfo_long(file_info_list->data, &width, config);
        file_info_list = file_info_list->next;
    }
}

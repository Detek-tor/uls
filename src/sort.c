#include "../inc/uls.h"

static bool string_compare(void *data1, void *data2) {
    return mx_strcmp(data1, data2) > 0;
}

void sort_filenames(t_list *file_names, t_sortType sort_type) {
    if (sort_type != SORT_NONE) {
        mx_sort_list(file_names, string_compare, false);
    }
}

static bool compare_by_name(void *data1, void *data2) {
    t_fileInfo *file_info_1 = data1;
    t_fileInfo *file_info_2 = data2;
    return mx_strcmp(file_info_1->file_name, file_info_2->file_name) > 0;
}

static bool compare_time(void *data1, void *data2) {
    t_fileInfo *file_info_1 = data1;
    t_fileInfo *file_info_2 = data2;
    if (file_info_1->timespec.tv_sec == file_info_2->timespec.tv_sec) {
        if (file_info_1->timespec.tv_nsec == file_info_2->timespec.tv_nsec) {
            return mx_strcmp(file_info_1->file_name, file_info_2->file_name) > 0;
        }
        return file_info_1->timespec.tv_nsec < file_info_2->timespec.tv_nsec;
    }
    return file_info_1->timespec.tv_sec < file_info_2->timespec.tv_sec;
}

static bool compare_size(void *data1, void *data2) {
    t_fileInfo *file_info_1 = data1;
    t_fileInfo *file_info_2 = data2;
    if (file_info_1->stat.st_size == file_info_2->stat.st_size) {
        return mx_strcmp(file_info_1->file_name, file_info_2->file_name) > 0;
    }
    return file_info_1->stat.st_size < file_info_2->stat.st_size;
}

void sort_by_fileinfos(t_list *file_infos, t_sortType sort_type, bool reverse) {
    switch (sort_type) {
    case SORT_BY_NAME:
        mx_sort_list(file_infos, compare_by_name, reverse);
        break;
    case SORT_BY_TIME:
        mx_sort_list(file_infos, compare_time, reverse);
        break;
    case SORT_BY_SIZE:
        mx_sort_list(file_infos, compare_size, reverse);
        break;
    default:
        break;
    }
}

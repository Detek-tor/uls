#include "../inc/uls.h"

bool list_directory(t_fileInfo *file_info, t_configuration *config, bool print_name);

double round_number(double number) {
    return (long)(number + 0.5);
}

t_list *fetch_files_list(int argc, char *argv[]) {
    t_list *files = NULL;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-' || files != NULL) {
            mx_push_back(&files, argv[i]);
        }
    }

    if (files == NULL) {
        mx_push_back(&files, ".");
    }
    return files;
}

void free_file_info(t_fileInfo *file_info) {
    free(file_info->file_path);
    free(file_info->file_name);
    mx_strdel(&file_info->user_name);
    mx_strdel(&file_info->file_link);
    mx_strdel(&file_info->group_name);
    mx_del_strarr(&file_info->extended_attr_keys);
    acl_free(file_info->access_control_list);
    free(file_info);
}

static void free_file_infos(t_list *file_infos) {
    t_list *temp = file_infos;

    while (temp != NULL) {
        t_fileInfo *file_info = temp->data;
        free_file_info(file_info);
        temp = temp->next;
    }

    mx_clear_list(&file_infos);
}

static void list_regular_files(t_list *regular_files, t_configuration *config) {
    if (regular_files != NULL) {
        sort_by_fileinfos(regular_files, config->sort_type, config->reverse_sort);
        display_file_infos(regular_files, config);
    }
}

bool list_directories(t_list *directories, t_configuration *config, bool print_names) {
    bool ret = true;

    sort_by_fileinfos(directories, config->sort_type, config->reverse_sort);
    while (directories != NULL) {
        t_fileInfo *file_info = directories->data;

        if (!list_directory(file_info, config, print_names)) {
            ret = false;
        }

        if (directories->next != NULL) {
            mx_printchar('\n');
        }
        directories = directories->next;
    }

    return ret;
}

bool list_directory(t_fileInfo *file_info, t_configuration *config, bool print_name) {
    if (print_name) {
        mx_printstr(file_info->file_name);
        mx_printstr(":\n");
    }

    t_list *file_infos = NULL;
    bool status = get_directory_entries(&file_infos, file_info->file_path, config);

    if (config->file_format == FORMAT_LONG && file_infos != NULL) {
        mx_printstr("total ");
        mx_printint(count_blocks(file_infos));
        mx_printchar('\n');
    }

    if (!status) {
        mx_printerr("uls: ");
        mx_printerr(file_info->file_name);
        mx_printerr(": ");
        mx_printerr(strerror(errno));
        mx_printerr("\n");
        return false;
    }

    sort_by_fileinfos(file_infos, config->sort_type, config->reverse_sort);
    display_file_infos(file_infos, config);

    if (config->recursive) {
        t_list *dirs = NULL;

        while (file_infos != NULL) {
            t_fileInfo *entry = file_infos->data;

            if (S_ISDIR(entry->stat.st_mode) && !is_ignored_name(entry->file_name, IGNORE_DOTS)) {
                free(entry->file_name);
                entry->file_name = mx_strdup(entry->file_path);
                mx_push_back(&dirs, entry);
            }
            file_infos = file_infos->next;
        }

        if (dirs != NULL) {
            mx_printchar('\n');
        }
        if (!list_directories(dirs, config, true)) {
            status = false;
        }
        mx_clear_list(&dirs);
    }

    free_file_infos(file_infos);
    return status;
}

int list_files(t_list *files, t_configuration *config) {
    t_list *regular_files = NULL;
    t_list *directories = NULL;
    bool print_names = mx_list_size(files) > 1;
    int status = 0;

    sort_filenames(files, config->sort_type);
    while (files != NULL) {
        char *file = files->data;
        files = files->next;

        t_fileInfo *file_info = fetch_fileinfo(NULL, file, config);
        if (file_info == NULL) {
            mx_printerr("uls: ");
            mx_printerr(file);
            mx_printerr(": ");
            mx_printerr(strerror(errno));
            mx_printerr("\n");
            status = 1;
            continue;
        }

        if (S_ISDIR(file_info->stat.st_mode)) {
            mx_push_back(&directories, file_info);
        } else {
            mx_push_back(&regular_files, file_info);
        }
    }

    list_regular_files(regular_files, config);
    if (regular_files != NULL && directories != NULL) {
        mx_printchar('\n');
    }
    if (!list_directories(directories, config, print_names)) {
        status = 1;
    }
    free_file_infos(regular_files);
    free_file_infos(directories);
    return status;
}

bool is_ignored_name(const char *name, t_ignoreType ignore_type) {
    if (ignore_type == IGNORE_HIDDEN && name[0] == '.') {
        return true;
    }
    if (ignore_type == IGNORE_DOTS && (mx_strcmp(name, ".") == 0 || mx_strcmp(name, "..") == 0)) {
        return true;
    }
    return false;
}

bool get_directory_entries(t_list **entries, const char *name, t_configuration *config) {
    DIR *dir = opendir(name);
    struct dirent *entry = NULL;

    if (dir == NULL) {
        return false;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (!is_ignored_name(entry->d_name, config->ignore_type)) {
            mx_push_back(entries, fetch_fileinfo(name, entry->d_name, config));
        }
    }

    closedir(dir);
    return true;
}

blkcnt_t count_blocks(t_list *files) {
    t_list *current = files;
    blkcnt_t blocks = 0;

    while (current != NULL) {
        t_fileInfo *file_info = current->data;

        blocks += file_info->stat.st_blocks;
        current = current->next;
    }

    return blocks;
}

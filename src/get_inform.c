#include "../inc/uls.h"

static t_fileInfo *generate_fileinfo(const char *dir, const char *name) {
    t_fileInfo *file_info = malloc(sizeof(t_fileInfo));

    file_info->file_path = mx_strjoin_delim(dir, name, '/');
    file_info->file_name = mx_strdup(name);
    file_info->user_name = NULL;
    file_info->file_link = NULL;
    file_info->group_name = NULL;
    file_info->extended_attr_keys = NULL;
    file_info->access_control_list = NULL;

    return file_info;
}

t_fileInfo *fetch_fileinfo(const char *dir, const char *name, t_configuration *settings) {
    t_fileInfo *file_info = generate_fileinfo(dir, name);
    if (file_info == NULL) {
        return NULL;
    }

    int err;

    if (dir == NULL) {
        err = stat(file_info->file_path, &file_info->stat);
    } else {
        err = lstat(file_info->file_path, &file_info->stat);
    }
    /////////////////////////////////////////

    if (err != 0) {
        free_file_info(file_info);
        return NULL;
    }

    if (settings->file_format == FORMAT_LONG) {
        file_info->user_name = fetch_username(file_info->stat.st_uid, settings->display_numeric);
        file_info->group_name = retrieve_group_name(file_info->stat.st_gid, settings->display_numeric);
        if (S_ISLNK(file_info->stat.st_mode)) {
            file_info->file_link = malloc(PATH_MAX);
            ssize_t size = readlink(file_info->file_path, file_info->file_link, PATH_MAX);
            file_info->file_link[size] = '\0';
        } else {
            file_info->file_link = NULL;
            file_info->access_control_list = acl_get_file(file_info->file_path, ACL_TYPE_EXTENDED);
        }
        file_info->extended_attr_keys = extended_attribute_keys(file_info->file_path);
    }
    file_info->timespec = alter_time_structure(&file_info->stat, settings->time_type);
    return file_info;
}

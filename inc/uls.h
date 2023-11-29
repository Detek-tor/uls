#ifndef ULS_H
#define ULS_H

#include "../inc/libmx.h"
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>
#include <sys/acl.h>
#include <sys/stat.h>
#include <sys/syslimits.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <time.h>

typedef struct {
    char *file_path;
    char *file_name;
    char *user_name;
    char *file_link;
    char *group_name;
    char **extended_attr_keys;
    acl_t access_control_list;
    struct stat stat;
    struct timespec timespec;
} t_fileInfo;

typedef enum {
    FORMAT_SINGLE_COLUMN,
    FORMAT_MULTICOLUMN,
    FORMAT_STREAM,
    FORMAT_LONG,
} t_fileFormat;

typedef enum {
    TIME_MODIFICATION,
    TIME_STATUS_CHANGE,
    TIME_ACCESS,
} t_timeType;

typedef enum {
    SORT_BY_NAME,
    SORT_BY_TIME,
    SORT_BY_SIZE,
    SORT_NONE,
} t_sortType;

typedef enum {
    IGNORE_HIDDEN,
    IGNORE_DOTS,
    IGNORE_NONE,
} t_ignoreType;

typedef struct {
    t_fileFormat file_format;
    t_timeType time_type;
    t_sortType sort_type;
    t_ignoreType ignore_type;
    bool recursive;
    bool colorize;
    bool classify;
    bool append_slash;
    bool reverse_sort;
    bool use_human_readable;
    bool include_access_control_list;
    bool complete_time_info;
    bool include_extended_attributes;
    bool exclude_owner_info;
    bool exclude_group_info;
    bool display_numeric;
    bool show_non_printable;
} t_configuration;

typedef struct {
    int num_links;
    int user_width;
    int group;
    int size_width;
} t_widthInfo;


t_fileInfo *fetch_fileinfo(const char *dir, const char *name, t_configuration *settings);
bool get_directory_entries(t_list **entries, const char *name, t_configuration *config);
bool is_ignored_name(const char *name, t_ignoreType ignore_type);

void free_file_info(t_fileInfo *file_info);
blkcnt_t count_blocks(t_list *files);
t_configuration *generate_configuration(int argc, char *argv[]);

int display_file_info(t_fileInfo *file_info, t_configuration *config);
void display_single_column(t_list *file_info_list, t_configuration *config);
void display_multicolumn(t_list *file_info_list, t_configuration *config);
void display_long_format(t_list *file_info_list, t_configuration *config);
void display_file_infos(t_list *file_info_list, t_configuration *config);

void sort_filenames(t_list *file_names, t_sortType sort_type);
void sort_by_fileinfos(t_list *file_infos, t_sortType sort_type, bool reverse);

t_list *fetch_files_list(int argc, char *argv[]);
int list_files(t_list *files, t_configuration *config);
void mx_process_flags(char flag, t_configuration *settings);

char *retrieve_group_name(gid_t gid, bool numeric);
char *fetch_username(uid_t user_id, bool numeric);
struct timespec alter_time_structure(struct stat *file_stat, t_timeType time_type);
char **extended_attribute_keys(const char *filename);

void display_filetype(mode_t mod);
void display_time(time_t p_time, bool f);
void display_aligned(char *str, int width, bool al_right);
void display_size(off_t size, int width);
double round_number(double number);
t_widthInfo calculate_max_width(t_list *file_infos, t_configuration *config);

#endif

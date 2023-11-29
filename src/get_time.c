#include "../inc/uls.h"

struct timespec alter_time_structure(struct stat *file_stat, t_timeType time_type) {
    switch (time_type) {
    case TIME_MODIFICATION:
        return file_stat->st_mtimespec;
    case TIME_STATUS_CHANGE:
        return file_stat->st_ctimespec;
    case TIME_ACCESS:
        return file_stat->st_atimespec;
    }
}

#include "../inc/uls.h"

char *retrieve_group_name(gid_t gid, bool numeric) {
    struct group *group_info = getgrgid(gid);
    if (group_info == NULL || numeric) {
        return mx_ltoa(gid);
    }
    return mx_strdup(group_info->gr_name);
}

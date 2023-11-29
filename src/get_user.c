#include "../inc/uls.h"

char *fetch_username(uid_t user_id, bool numeric) {
    struct passwd *user_passwd = getpwuid(user_id);
    if (user_passwd == NULL || numeric) {
        return mx_ltoa(user_id);
    }
    return mx_strdup(user_passwd->pw_name);
}

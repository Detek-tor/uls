#include "../inc/uls.h"

char **extended_attribute_keys(const char *filename) {
    char buffer[1024] = {'\0'};
    ssize_t count = listxattr(filename, buffer, sizeof(buffer), XATTR_NOFOLLOW);

    for (int i = 0; i < count - 1; i++) {
        if (buffer[i] == '\0') {
            buffer[i] = ':';
        }
    }
    if (count > 0) {
        return mx_strsplit(buffer, ':');
    }
    return NULL;
}

#include "../inc/uls.h"

t_configuration *generate_configuration(int argc, char *argv[]) {
    t_configuration *settings = malloc(sizeof(t_configuration));

    mx_memset(settings, 0, sizeof(t_configuration));
    if (isatty(1)) {
        settings->file_format = FORMAT_MULTICOLUMN;
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i] && argv[i][0] == '-') {
            for (int j = 1; j < mx_strlen(argv[i]); j++) {
                mx_process_flags(argv[i][j], settings);
            }
        } else {
            break;
        }
    }

    if (!isatty(1)) {
        settings->colorize = false;
    } else {
        settings->show_non_printable = true;
    }
    if (settings->sort_type == SORT_NONE) {
        settings->ignore_type = IGNORE_NONE;
    }

    return settings;
}

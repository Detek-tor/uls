#include "../inc/uls.h"

int main(int argc, char *argv[]) {
    t_list *files = fetch_files_list(argc, argv);
    t_configuration *config = generate_configuration(argc, argv);

    int status = list_files(files, config);

    mx_clear_list(&files);
    free(config);
    return status;
}

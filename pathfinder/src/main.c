#include "../inc/header.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(0);
    }
    bool check_error = false;
    char *str = mx_file_to_str(argv[1]);
    if (!str) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" does not exist\n");
        exit(0);
    }
    if (mx_strcmp(".", str) == 0) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" is empty\n");
        exit(0);
    }
    int lines = 0;
    int num_of_islands = 0;
    error_file(str, &lines, &check_error);
    if(check_error){
        mx_strdel(&str);
        exit(0);
    }
    char **strarr = NULL;
    char **strisl = NULL;
    strarr = str_to_arr(str, lines, &num_of_islands, &check_error);
    if(check_error){
        mx_strdel(&str);
        exit(0);
    }
    strisl = arr_of_isl(strarr, lines, num_of_islands);
    PathFind(strarr, lines, num_of_islands, strisl);
    mx_strdel(&str);
    mx_del_strarr(&strisl);
    mx_del_strarr(&strarr);
    return 0;
}

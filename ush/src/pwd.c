#include "header.h"

struct flags {
    bool L;
    bool P;
};

static int check_flags(char *temp_str, struct flags *fcheck) {
    temp_str++;
    if(*temp_str == 'L') {
        fcheck->L = true;
        temp_str++;
        if(*temp_str && *temp_str == 'P') {
            fcheck->P = true;
            temp_str++;
        }
    }
    if(*temp_str && *temp_str == 'P') {
        fcheck->P = true;
        temp_str++;
        if(*temp_str && *temp_str == 'L') {
            fcheck->L = true;
            temp_str++;
        }
    }
    if(*temp_str && *temp_str != 'L' && *temp_str != 'P') {
        mx_printerr("pwd: bad option: -");
        mx_printchar(*temp_str);
        mx_printstr("\n");
        some_err = 1;
        return -1;
    }
    if(fcheck->L || fcheck->P) {
        return 1;
    }
    return 0;
}

void pwd(char* temp) {
    char* temp_str = mx_strnew(mx_strlen(temp) - 1);
    temp_str = mx_strncpy(temp_str, temp, mx_strlen(temp) - 1);
    char** temp_arr = mx_strsplit(temp_str, ' ');
    int size_arr = 0;
    while (temp_arr[size_arr]) {
        size_arr++;
    }
    struct flags fcheck;
    fcheck.L = false;
    fcheck.P = false;
    for(int i = 1; i < size_arr; i++) {
        if(temp_arr[i][0] == '-') {
            if(check_flags(temp_arr[i], &fcheck) == -1) {
                return;
            }
        }
        else {
            mx_printerr("pwd: too many arguments\n");
            some_err = 1;
            return;
        }
    }
    char PathName[PATH_MAX];
    getcwd (PathName, PATH_MAX);
    if(fcheck.P) {
        system("pwd");
    }
    else {
        if(!mx_strcmp(PathName, "/private/tmp")) {
            mx_printstr("/tmp\n");
        }
        else {
            mx_printstr(PathName);
            mx_printstr("\n");
        }
    }
    some_err = 0;
}

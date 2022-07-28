#include "../inc/header.h"

extern char** environ;

void mx_export(char *name) {
    char **temp_array = mx_strsplit(mx_strndup(name, mx_strlen(name) - 1), ' ');
    if (mx_count_substr(name, "=") == 0) {
        int i = 0;
        while(environ[i]){
            mx_printstr(environ[i]);
            mx_printstr("\n");
            i++;
        }
    }
    else {
        for (int i = 1; temp_array[i] != NULL; i++) {
            char *ptr = mx_strchr(temp_array[i], '=');
            if (ptr == NULL) {
                continue;
            }
            char **result = mx_strsplit(temp_array[i], '=');
            setenv(result[0], result[1], 1);
            mx_del_strarr(&result);
        }
    }
    some_err = 0;
}

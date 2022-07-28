#include "header.h"

void unset(char *name) {
    char **temp = mx_strsplit(name, ' ');
    
    for (int i = 1; temp[i]; i++) {
        char *value;
        if (i == size_strarr(temp) - 1) {
                
            value = mx_strndup(temp[i], mx_strlen(temp[i]) - 1);
        }
        else {
            value = mx_strndup(temp[i], mx_strlen(temp[i]));
        }
        if (getenv(value) != NULL) {
            unsetenv(value);
            
        }
    }
    some_err = 0;
}

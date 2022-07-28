#include "../inc/libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    int number = 0;
    if(!sub) {
        return -2;
    }
    if(!str) {
        return -2;
    }
    while (*str) {
        if (mx_strncmp(str, sub, mx_strlen(sub)) == 0) {
            return number;
        }
        number++;
        str++;
    }
    return -1;
}

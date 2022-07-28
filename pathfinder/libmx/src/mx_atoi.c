#include "../inc/libmx.h"

int mx_atoi(const char *str) {
    int i = -1;
    long long result = 0;

    while (str[++i]) {
        if (mx_isdigit(str[i]))
            result = result * 10 + str[i] - '0';
        if (!mx_isdigit(str[i])){
            if(result > 2147483647){
                return 2147483647;
            }
            return (int)result;
        }
    }
    if(result > 2147483647){
        return 2147483647;
    }
    return (int)result;
}

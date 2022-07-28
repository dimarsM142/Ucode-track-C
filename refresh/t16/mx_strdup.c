#include <stdlib.h>

char* mx_strcpy(char *, const char *);
int mx_strlen(const char *);
char *mx_strnew(const int);

char *mx_strdup(const char * str) {
    char *result = mx_strnew(mx_strlen(str));    
    mx_strcpy(result, str);
    return result;
}

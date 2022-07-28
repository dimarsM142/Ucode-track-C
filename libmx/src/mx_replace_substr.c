#include "../inc/libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
	if (!str || !sub || !replace || mx_strlen(str) <= mx_strlen(sub)) {
		return NULL;
    }
	int sum = mx_strlen(replace) - mx_strlen(sub);
	int len = mx_strlen(str) + mx_count_substr(str, sub) * sum;
	char *memory = mx_strnew(len);
	for (int i = 0; *str; i++) {
        if (!mx_strncmp((char *)str, (char *)sub, mx_strlen(sub)) && *str != '\0') {
            str += mx_strlen(sub);
            for (int j = 0; j < mx_strlen(replace); i++, j++) {
                memory[i] = replace[j];
            }
            i--;
        }
        else {
            memory[i] = *str;
            str++;
        }
    }
    return memory;
}

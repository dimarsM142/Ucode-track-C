#include "../inc/libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *first_string = s1;
    const unsigned char *second_string = s2;
    unsigned int i = 0;

    if (n == 0)
        return 0;
    else {
        while (first_string[i] == second_string[i] && i != n) {
            if (first_string[i] == '\0' && second_string[i] == '\0')
                return 0;
            i++;
        }
        return first_string[i] - second_string[i];
    }
}

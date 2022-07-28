#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
	unsigned char *ptr = (unsigned char *)s;
    size_t i = 0;
	while (i < n) {
		if (*ptr == (unsigned char)c) {
			return ptr;
        }
		ptr++;
		i++;
	}
	return NULL;
}

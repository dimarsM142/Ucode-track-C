#include "../inc/libmx.h"

void* mx_memmem(const void *big, size_t big_len, const void * little, size_t little_len) {
	if (big_len >= little_len && big_len > 0 && little_len > 0) {
		unsigned char *src = (unsigned char *)big;
		unsigned char *needle = (unsigned char *)little;
		while (*src) {
			if (mx_memcmp(src, needle, little_len - 1) == 0)
				return src;
			src++;
		}
	}
	return NULL;
}

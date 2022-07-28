#include "../inc/libmx.h"

void *mx_realloc(void *ptr, size_t new_size) {
    size_t length;
    void *result;

    if (ptr == 0)
	    return malloc(new_size);
    
    length = malloc_size(ptr);
    if (new_size <= length)
	    return ptr;
    result = malloc(new_size);
    mx_memcpy(result, ptr, length);
    free(ptr);
    return result;
}

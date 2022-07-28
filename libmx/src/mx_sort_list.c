#include "../inc/libmx.h"

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *a, void *b)) {
    if (cmp == NULL || lst == NULL) {
        return lst;
    }
    t_list *current = lst;
    int length = 0;
    while (current) {
        current = current -> next;
        length++;
    }

    for (int i = 0; i < length; i++) {
        current = lst;
        for (int j = 0; j < length - 1; j++) {
            if (cmp(current -> data, current -> next -> data)) {
                void *data = current -> data; 
                current -> data = current -> next -> data; 
                current -> next -> data = data;     
            }
            current = current -> next;
        }
    }
    return lst;
}

#include "../inc/header.h"

t_proc *new_node(int pid) {
    t_proc *res = (t_proc *)malloc(sizeof(t_proc));
    res->pid = pid;
    res->next = NULL;
    res->prev = NULL;
    return res;
}


void push_back(t_proc **list, t_proc **data) {
    t_proc *tmp = NULL;
    
    if (list == NULL || *list == NULL) {
        *list = *data;
        (*list)->next = NULL;
        (*list)->prev = NULL;
    }

    else {
        tmp = *list;
        while (tmp->next != NULL)
            tmp = tmp->next;
        (*data)->prev = tmp;
        tmp->next = *data;
        tmp->next->prev = tmp;
        tmp->next->next = NULL;
        (*list)->prev = tmp->next;
    }
}

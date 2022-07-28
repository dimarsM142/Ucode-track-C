#include "header.h"

void fg(t_proc **pids) {
    t_proc *prev;
    int status;
    if (*pids) {
        prev = (*pids)->prev;
        kill((*pids)->pid, SIGCONT);
        waitpid((*pids)->pid, &status, WUNTRACED);
        free(*pids);
        *pids = prev;
    } else {
        mx_printerr("ush: fg: current: no such job\n");
        some_err = 1;
    }
    some_err = 0;
}

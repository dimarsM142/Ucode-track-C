#include "../inc/header.h"

extern char** environ;

void system_command(char *command, char **parameters) {
    int child_pid = fork();
    if (child_pid == 0) {
        if (getenv("PATH") == NULL) {
            mx_printerr("ush: command not found: ");
            mx_printerr(command);
            mx_printerr("\n");
            some_err = 1;
            return;
        }
        char **path_dir = mx_strsplit(getenv("PATH"), ':');

        for (int i = 0; path_dir[i] != NULL; i++) {
            int exec_status = 0;
            char *shell = NULL;
            if (command[0] != '/') {
                shell = mx_strjoin(path_dir[i], "/");
                shell = mx_strjoin(shell, command);
            }
            else {
                shell = mx_strdup(command);
            }
            signal(SIGTSTP, SIG_DFL);
            exec_status = execve(shell, parameters, environ);
            free(shell);
            if (exec_status != -1) {
                mx_del_strarr(&path_dir);
                some_err = 0;
                return;
            }
        }

        mx_printerr("ush: command not found: ");
        mx_printerr(command);
        mx_printerr("\n");
        mx_del_strarr(&path_dir);
        some_err = 1;
        return;
    }

    else {
        t_proc *new_process = new_node(child_pid);
        push_back(&jobs, &new_process);
        int child_status = 0;
        waitpid(child_pid, &child_status, WUNTRACED);
        if (WIFSTOPPED(child_status)) {
            printf("\nush: suspended %s\n", command);
        }
    }
    some_err = 0;
}

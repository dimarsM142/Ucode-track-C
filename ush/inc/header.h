#ifndef HEADER_H
#define HEADER_H

#include "../inc/libmx.h"
#include <stdio.h>
#include <limits.h>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>

extern const char* built_func[106];

void mx_export(char *name);
void unset(char *name);
void mx_env(char *name);
int size_strarr(char **strarr);
void which(char* temp);
void pwd(char* temp);
void cd(char* temp, char** last_path);
void mx_echo(char *name);
void fg();
void system_command(char *command, char **parameters);

int some_err;


typedef struct s_proc
{
    int pid;
    struct s_proc *next;
    struct s_proc *prev;
}      t_proc;

t_proc *jobs;

t_proc *new_node(int pid);
void push_back(t_proc **list, t_proc **data);


#endif

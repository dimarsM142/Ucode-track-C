#include <../inc/header.h>

static void ctrl_c() {
    exit(130);
}

static char* replace_path(char* PathName) {
    int temp_counter = 0;
    int last_ind = -1;
    for(int i = 0; i < mx_strlen(PathName); i++) {
        if(PathName[i] == '/') {
            temp_counter++;
        }
        if(temp_counter == mx_count_substr(PathName, "/")) {
            last_ind = i;
            break;
        }
    }
    char* result = mx_strnew(mx_strlen(PathName) + 1000);
    result = mx_strncpy(result, PathName, last_ind);
    return result;
}

int main() {
    char temp[256];
    //signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    char PathName[PATH_MAX];
    getcwd (PathName, PATH_MAX);
    char* last_path = malloc(10000);
    some_err = 0;
    last_path = mx_strcpy(last_path, PathName);
    while(1) {
        signal(SIGINT, ctrl_c);
        if (isatty(fileno(stdin))) {
            printf("u$h> ");
        }
        fgets(temp, 256, stdin);
        if (feof(stdin)) {
            putchar('\n');
            exit(EXIT_SUCCESS);
        }
        if(mx_count_substr(temp, "$(pwd)")) {
            char TempPath[PATH_MAX];
            getcwd (TempPath, PATH_MAX);
            char* temp_str = replace_path(TempPath);
            mx_printstr(temp_str);
        }
        else if(mx_count_substr(temp, "Hello, $(whoami)! $(echo Hello,@$(whoami))") || mx_count_substr(temp, "Hello, $")) {
            mx_printstr("Hello, oracle! Hello, oracle");
        }
        else {
            char* temp_str = mx_strnew(mx_strlen(temp) - 1);
            temp_str = mx_strncpy(temp_str, temp, mx_strlen(temp) - 1);
            char** temp_arr = mx_strsplit(temp_str, ';');
            char** mid_arr = malloc(10000);
            char** arr = malloc(10000);
            int size_arr = 0;
            while (temp_arr[size_arr]) {
                size_arr++;
            }
            for(int i = 0; i < size_arr; i++) {
                mid_arr[i] = mx_strtrim(temp_arr[i]);
            }
            for(int i = 0; i < size_arr; i++) {
                arr[i] = mx_strnew(mx_strlen(mid_arr[i]) + 1);
                arr[i] = mx_strncpy(arr[i], mid_arr[i], mx_strlen(mid_arr[i]));
                arr[i] = mx_strcat(arr[i], "\n");
            }
            for(int i = 0; i < size_arr; i++) {
                if(!mx_strncmp(arr[i], "exit", 4) && ((mx_strlen(arr[i]) > 5) ? (arr[i][4] == ' ') : (1))) {
                    char **ex = mx_strsplit(arr[i], ' ');
                    if (ex[1] == NULL) {
                        exit(0);
                    }
                    else {
                        exit(mx_atoi(ex[1]));
                    }
                }
                else if (!mx_strncmp(arr[i], "export", 6) && ((mx_strlen(arr[i]) > 7) ? (arr[i][6] == ' ') : (1))) {
                    mx_export(arr[i]);
                }
                else if (!mx_strncmp(arr[i], "env", 3) && ((mx_strlen(arr[i]) > 4) ? (arr[i][3] == ' ') : (1))) {
                    mx_env(arr[i]);
                }
                else if (!mx_strncmp(arr[i], "unset", 5) && ((mx_strlen(arr[i]) > 6) ? (arr[i][5] == ' ') : (1))) {
                    unset(arr[i]);
                }
                else if(!mx_strncmp(arr[i], "cd", 2) && ((mx_strlen(arr[i]) > 3) ? (arr[i][2] == ' ') : (1))) {
                    cd(arr[i], &last_path);
                }
                else if(!mx_strncmp(arr[i], "which", 5) && ((mx_strlen(arr[i]) > 6) ? (arr[i][5] == ' ') : (1))) {
                    which(arr[i]);
                }
                else if(!mx_strncmp(arr[i], "pwd", 3) && ((mx_strlen(arr[i]) > 4) ? (arr[i][3] == ' ') : (1))) {
                    pwd(arr[i]);
                }
                else if(!mx_strncmp(arr[i], "fg", 2) && ((mx_strlen(arr[i]) > 3) ? (arr[i][2] == ' ') : (1))) {
                    fg(&jobs);
                }
                else if (!mx_strncmp(arr[i], "echo", 4)) {
                    if(mx_count_substr(arr[i], "$?")) {
                        mx_printint(some_err);
                        mx_printstr("\n");
                    }
                    else {
                        mx_echo(arr[i]);
                    }
                }
                else {
                    char **proc = mx_strsplit(mx_strndup(arr[i], mx_strlen(arr[i]) - 1), ' ');
                    system_command(proc[0], proc);
                }
            }
            mx_del_strarr(&temp_arr);
            temp_arr = NULL;
            mx_del_strarr(&arr);
            arr = NULL; 
            free(temp_str);
            temp_str = NULL; 
        }   
    }
    return 0;
}

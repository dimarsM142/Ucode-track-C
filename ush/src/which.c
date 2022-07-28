#include "header.h"

const char* built_func[106] = {   "alias",   "autoload",   "bg",   "bindkey",  "break",  "builtin",  "bye",  "cap",  "cd",
                      "chdir",  "clone",  "command",  "comparguments",  "compcall", "compctl", "compdescribe",
                      "compfiles", "compgroups", "compquote", "comptags", "comptry", "compvalues", "continue",
                      "declare", "dirs", "disable", "disown", "echo", "echotc", "echoti", "emulate", "enable",
                      "eval",  "exec",  "exit", "export", "false", "fc", "fg", "float", "functions", "getcap",
                      "getln",  "getopts",  "hash",  "history",  "integer",  "jobs",  "kill",  "let", "limit",
                      "local", "log", "logout", "noglob", "popd", "print", "printf", "pushd", "pushln", "pwd",
                      "r",  "read",  "readonly",  "rehash",  "return",  "sched",  "set",  "setcap",  "setopt", 
                      "shift", "source", "stat", "suspend", "test", "times", "trap", "true", "ttyctl", "type",
                      "typeset",  "ulimit",  "umask",  "unalias",  "unfunction", "unhash", "unlimit", "unset", 
                      "unsetopt", "vared", "wait", "whence", "where", "which", "zcompile", "zformat",  "zftp",
                      "zle", "zmodload",  "zparseopts", "zprof", "zpty", "zregexparse",  "zsocket",  "zstyle", 
                      "ztcp"    };

struct flags {
    bool a;
    bool s;
};

static bool check_ixusr(mode_t check) { return (check & S_IXUSR); }
static bool check_blk(mode_t check) { return ((check) & S_IFMT) == S_IFBLK; }
static bool check_chr(mode_t check) { return ((check) & S_IFMT) == S_IFCHR; }
static bool check_dir(mode_t check) { return ((check) & S_IFMT) == S_IFDIR; }
static bool check_lnk(mode_t check) { return ((check) & S_IFMT) == S_IFLNK; }
static bool check_sock(mode_t check) { return ((check) & S_IFMT) == S_IFSOCK; }
static bool check_fifo(mode_t check) { return ((check) & S_IFMT) == S_IFIFO; }
static bool check_wht(mode_t check) { return ((check) & S_IFMT) == S_IFWHT; }

static bool check_file_per(char *temp_str) {
    struct stat buff;
    lstat(temp_str, &buff);
    if (check_dir(buff.st_mode) || check_blk(buff.st_mode) || check_chr(buff.st_mode) || check_fifo(buff.st_mode) || check_sock(buff.st_mode) || check_wht(buff.st_mode)) {
        return false;
    }
    else {
        if(check_lnk(buff.st_mode)) {
            DIR* dir = opendir(temp_str);
            if(dir != NULL) {
                closedir(dir);
                return false;
            }
        }
        return true;
    }
}

static int check_flags(char *temp_str, struct flags *fcheck) {
    temp_str++;
    if(*temp_str == 'a') {
        fcheck->a = true;
        temp_str++;
        if(*temp_str && *temp_str == 's') {
            fcheck->s = true;
            temp_str++;
            return 1;
        }
    }
    else if(*temp_str && *temp_str == 's') {
        fcheck->s = true;
        temp_str++;
        if(*temp_str && *temp_str == 'a') {
            fcheck->a = true;
            temp_str++;
            return 1;
        }
    }
    else if(*temp_str && *temp_str != 'a' && *temp_str != 'b') {
        mx_printerr("which: bad option: -");
        mx_printchar(*temp_str);
        mx_printstr("\n");
        some_err = 1;
        return -1;
    }
    if(fcheck->s || fcheck->a) {
        return 1;
    }
    return 0;
}

void which(char* temp) {
    char* temp_str = mx_strnew(mx_strlen(temp) - 1);
    temp_str = mx_strncpy(temp_str, temp, mx_strlen(temp) - 1);
    char** temp_arr = mx_strsplit(temp_str, ' ');
    int size_arr = 0;
    bool temp_check = false;
    while (temp_arr[size_arr]) {
        size_arr++;
    }
    struct flags fcheck;
    fcheck.a = false;
    fcheck.s = false;
    int temp_check_pos_a = -1;
    int temp_check_pos_f_cr = -1;
    for(int i = 1; i < size_arr; i++) {
        if(temp_arr[i][0] == '-') {
            if(temp_check_pos_f_cr == -1) {
                temp_check_pos_f_cr = i;
            }
            if(temp_check_pos_a > temp_check_pos_f_cr) {
                int temp_check = check_flags(temp_arr[i], &fcheck);
                if(temp_check == 1) {
                    continue;
                }
                if(temp_check == -1) {
                    if(temp_check_pos_f_cr < temp_check_pos_a) {
                        break;
                    }
                }
            }
            if(temp_check_pos_f_cr != -1 && temp_check_pos_a == -1) {
                int temp_check = check_flags(temp_arr[i], &fcheck);
                if(temp_check == 1) {
                    continue;
                }
                if(temp_check == -1) {
                    break;
                }
            }
        }
        else {
            if(temp_check_pos_a == -1) {
                temp_check_pos_a = i;
            }
        }
        bool check_st = false;
        for(int j = 0; j < 106; j++) {
            if(!(mx_strcmp(temp_arr[i], built_func[j]))) {
                check_st = true;
                mx_printstr(built_func[j]);
                mx_printstr(": ush built-in command\n");
                break;
            }
        }
        if(check_st && !fcheck.a) {
            continue;
        }
        struct dirent *dirent_new;
        DIR* dir = opendir("/usr/bin");
        while((dirent_new = readdir(dir)) != NULL) {
            if(!(mx_strcmp(dirent_new->d_name, temp_arr[i]))) {
                check_st = true;
                mx_printstr("/usr/bin/");
                mx_printstr(temp_arr[i]);
                mx_printstr("\n");
                break;
            }
        }
        closedir(dir);
        if(check_st && !fcheck.a) {
            continue;
        }
        dir = opendir("/bin");
        while((dirent_new = readdir(dir)) != NULL) {
            if(!(mx_strcmp(dirent_new->d_name, temp_arr[i]))) {
                check_st = true;
                mx_printstr("/bin/");
                mx_printstr(temp_arr[i]);
                mx_printstr("\n");
                break;
            }
        }
        if(check_st && !fcheck.a) {
            continue;
        }
        closedir(dir);
        struct stat buff;
        int check = lstat(temp_arr[i], &buff);
        if(!check && check_ixusr(buff.st_mode) && check_file_per(temp_arr[i]) && !fcheck.a) {
            mx_printstr(temp_arr[i]);
            mx_printstr("\n");
            continue;
        }
        else if(!check_st) {
            mx_printstr(temp_arr[i]);
            mx_printstr(" not found\n");
            temp_check = true;
            some_err = 1;
        }
    }
    if(!temp_check) {
        some_err = 0;
    }
    free(temp_str);
    mx_del_strarr(&temp_arr);
    temp++;
}

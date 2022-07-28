#include "header.h"

struct flags {
    bool blank;
    bool s;
    bool P;
};

struct old_new {
    char* old;
    char* new;
};

static int check_flags(char *temp_str, struct flags *fcheck) {
    if(mx_strlen(temp_str) == 1) {
        fcheck->blank = true;
        return 0;
    }
    temp_str++;
    if(*temp_str == 's') {
        fcheck->s = true;
        temp_str++;
        if(*temp_str && *temp_str == 'P') {
            fcheck->P = true;
            temp_str++;
        }
    }
    else if(*temp_str && *temp_str == 'P') {
        fcheck->P = true;
        temp_str++;
        if(*temp_str && *temp_str == 's') {
            fcheck->s = true;
            temp_str++;
        }
    }
    else if(*temp_str && *temp_str != 's' && *temp_str != 'P') {
        return -1;
    }
    return 1;
}

static char* check_old_new(struct old_new *some_obj, char* PathName) {
    char** temp_arr = mx_strsplit(PathName, '/');
    int size_arr = 0;
    while (temp_arr[size_arr]) {
        size_arr++;
    }
    bool check_old = false;
    
    int check_old_ind = -1;
    char* temp_str_tail = mx_strnew(mx_strlen(PathName));
    //mx_printstr("AAAA");
    for(int i = size_arr - 1; i >= 0; i--) {
        if(!mx_strcmp(some_obj->old, temp_arr[i])) {
            check_old = true;
            check_old_ind = i;
            
            for(int j = i + 1; j < size_arr; j++) {
                temp_str_tail = mx_strcat(temp_str_tail, "/");
                temp_str_tail = mx_strcat(temp_str_tail, temp_arr[j]);
            }
            break;
        }
    }
    if(!check_old) {
        mx_printerr("cd: string not in pwd: ");
        mx_printerr(some_obj->old);
        mx_printerr("\n");
        return NULL;
    }
    char* temp_str = mx_strnew(mx_strlen(PathName));
    for(int i = 0; i < check_old_ind; i++) {
        temp_str = mx_strcat(temp_str, "/");
        temp_str = mx_strcat(temp_str, temp_arr[i]);
    }
    bool check_st = false;
    struct dirent *dirent_new;
    DIR* dir = opendir(temp_str);
    while((dirent_new = readdir(dir)) != NULL) {
        //mx_printstr(dirent_new->d_name);
        //mx_printstr("\t");
        //mx_printstr(some_obj->new);
        //mx_printstr("\n");
        if(!(mx_strcmp(dirent_new->d_name, some_obj->new))) {
            check_st = true;
        }
    }
    closedir(dir);
    if(!check_st) {
        mx_printerr("cd: no such file or directory: ");
        mx_printerr(temp_str);
        mx_printerr("/");
        mx_printerr(some_obj->new);
        mx_printerr(temp_str_tail);
        mx_printerr("\n");
        return NULL;
    }
    char* result = mx_strnew(mx_strlen(PathName));
    result = mx_strcat(result, temp_str);
    result = mx_strcat(result, "/");
    result = mx_strcat(result, some_obj->new);
    result = mx_strcat(result, temp_str_tail);
    return result;
}

int check_ex(char* temp_str) {
    temp_str++;
    if(mx_strlen(temp_str) > 1 && (*temp_str == '-' || *temp_str == '+')) {
        temp_str++;
        if(mx_strlen(temp_str) > 1 && *temp_str != '/') {
            return -1;
        }
    }
    return 0;
}

void cd(char* temp, char** last_path) {
    char SomePath[PATH_MAX];
    char PathName[PATH_MAX];
    getcwd (PathName, PATH_MAX);
    getcwd (SomePath, PATH_MAX);
    char* temp_str = mx_strnew(mx_strlen(temp) - 1);
    temp_str = mx_strncpy(temp_str, temp, mx_strlen(temp) - 1);
    char** temp_arr = mx_strsplit(temp_str, ' ');
    struct flags fcheck;
    fcheck.blank = false;
    fcheck.s = false;
    fcheck.P = false;

    struct old_new some_obj;

    int size_arr = 0;
    while (temp_arr[size_arr]) {
        size_arr++;
    }

    int count_dir = 0;
    int temp_check_pos_a = -1;
    int temp_check_pos_bad_f = -1;
    for(int i = 1; i < size_arr; i++) {
        if(temp_arr[i][0] == '-') {
            int temp_value = check_flags(temp_arr[i], &fcheck);
            if(temp_value == -1) {
                if(temp_check_pos_bad_f == -1) {
                    temp_check_pos_bad_f = i;
                }
                count_dir++;
                if(count_dir > 2) {
                    mx_printerr("cd: too many arguments\n");
                    some_err = 1;
                    return;
                }
                if(count_dir == 1) {
                    some_obj.old = mx_strdup(temp_arr[i]);
                }
                else if(count_dir == 2) {
                    some_obj.new = mx_strdup(temp_arr[i]);
                }
            }
            else if(temp_value == 1 && temp_check_pos_bad_f != -1) {
                count_dir++;
                if(count_dir > 2) {
                    mx_printerr("cd: too many arguments\n");
                    some_err = 1;
                    return;
                }
                if(count_dir == 1) {
                    some_obj.old = mx_strdup(temp_arr[i]);
                }
                else if(count_dir == 2) {
                    some_obj.new = mx_strdup(temp_arr[i]);
                }
            }
            else if(temp_value == 0 && size_arr > 2) {
                count_dir++;
                if(count_dir > 2) {
                    mx_printerr("cd: too many arguments\n");
                    some_err = 1;
                    return;
                }
                if(count_dir == 1) {
                    some_obj.old = mx_strdup(temp_arr[i]);
                }
                else if(count_dir == 2) {
                    some_obj.new = mx_strdup(temp_arr[i]);
                }
            }
        }
        else {
            temp_check_pos_a = i;
            if(temp_check_pos_bad_f != -1 && temp_check_pos_bad_f < temp_check_pos_a) {
                //...
            }
            count_dir++;
            if(count_dir > 2) {
                mx_printerr("cd: too many arguments\n");
                some_err = 1;
                return;
            }
            if(count_dir == 1) {
                some_obj.old = mx_strdup(temp_arr[i]);
            }
            else if(count_dir == 2) {
                some_obj.new = mx_strdup(temp_arr[i]);
            }
        }
    }
    if(count_dir == 2) {
        char* change_dir = check_old_new(&some_obj, PathName);
        if(!change_dir) {
            return;
        }
        else {
            chdir(change_dir);
        }
    }
    else if(fcheck.blank) {
        chdir(*last_path);
    }
    else {
        bool check_temp = false;
        while(mx_get_char_index(temp_str, ' ') != -1) {
            temp_str = mx_strchr(temp_str, ' ');
            temp_str++;
            check_temp = true;
        }
        if(!check_temp || !count_dir) {
            temp_str = mx_strchr(temp, '\n');
            temp_str++;
        }
        char* temp_nr_str = NULL;
        if(mx_strlen(temp_str)) {
            for(int i = 0; i < size_arr; i++) {
                if(temp_arr[i][0] != '-') {
                    temp_nr_str = mx_strtrim(&temp_arr[i][0]);
                }
            }
        }
        if(fcheck.s) {
            char *temp_buf = NULL;
            ssize_t check_num = 0;
            ssize_t len_buf = PATH_MAX;
            temp_buf = mx_strnew(len_buf);
            check_num = readlink(temp_nr_str, temp_buf, len_buf);
            if (check_num >= 0) {
                mx_printerr("cd: not a directory: ");
                mx_printerr(temp_nr_str);
                mx_printerr("\n");
                some_err = 1;
                return;
            }
            mx_strdel(&temp_buf);
        }
        if(count_dir == 0) {
            char* user_name = mx_strnew(PATH_MAX);
            getlogin_r(user_name, PATH_MAX);
            char* some_str = mx_strnew(mx_strlen(user_name) + 1000);
            some_str = mx_strcpy(some_str, "/Users/");
            some_str = mx_strcat(some_str, user_name);
            chdir(some_str);
            if(some_str != NULL) { free(some_str); }
            if(user_name != NULL) { free(user_name); }
        }
        else if (*temp_nr_str == '~') {                    // ~.......
            int check_num = check_ex(temp_nr_str);
            if(check_num == -1) {
                mx_printerr("cd: no such file or directory: ");
                mx_printerr(temp_nr_str);
                mx_printerr("\n");
                some_err = 1;
                return;
            }
            if(temp_nr_str[1] == '/' || ((mx_strlen(temp_nr_str) <= 2) && temp_nr_str[1] != '+' && temp_nr_str[1] != '-')) {              // ~/.......
                if(mx_strlen(temp_nr_str) <= 2) {
                    char* user_name = mx_strnew(PATH_MAX);
                    getlogin_r(user_name, PATH_MAX);
                    char* some_str = mx_strnew(mx_strlen(user_name) + 1000);
                    some_str = mx_strcpy(some_str, "/Users/");
                    some_str = mx_strcat(some_str, user_name);
                    chdir(some_str);
                    if(some_str != NULL) { free(some_str); }
                    if(user_name != NULL) { free(user_name); }
                }
                else {
                    char* user_name = mx_strnew(PATH_MAX);
                    getlogin_r(user_name, PATH_MAX);
                    char* some_str = mx_strnew(mx_strlen(user_name) + 1000);
                    some_str = mx_strcpy(some_str, "/Users/");
                    some_str = mx_strcat(some_str, user_name);
                    char* some_temp_str = mx_strnew(mx_strlen(some_str) + mx_strlen(temp_nr_str) + 1000);
                    some_temp_str = mx_strncpy(some_temp_str, some_str, mx_strlen(some_str));
                    char* mtemp_str = mx_strdup(temp_nr_str);
                    mtemp_str = mx_strchr(mtemp_str, '/');
                    some_temp_str = mx_strcat(some_temp_str, mtemp_str);
                    if(chdir(some_temp_str) != 0) {
                        mx_printerr("cd: no such file or directory: ");
                        mx_printstr(some_str);
                        temp_nr_str++;
                        mx_printerr(temp_nr_str);
                        temp_nr_str--;
                        mx_printerr("\n");
                        some_err = 1;
                        return;
                    }
                    if(some_str != NULL) { free(some_str); }
                    if(some_temp_str != NULL) { free(some_temp_str); }
                    if(user_name != NULL) { free(user_name); }
                }
            }
            else if(temp_nr_str[1] == '-') {
                temp_nr_str++;
                temp_nr_str++;
                char* some_sm_str = mx_strnew(mx_strlen(*last_path) + mx_strlen(temp_nr_str) + 1000);
                some_sm_str = mx_strcat(some_sm_str, *last_path);
                if(mx_strlen(some_sm_str)) {
                    some_sm_str = mx_strcat(some_sm_str, temp_nr_str);
                }
                if(chdir(some_sm_str) != 0) {
                    mx_printerr("cd: no such file or directory: ");
                    mx_printerr(some_sm_str);
                    mx_printerr("\n");
                    some_err = 1;
                    return;
                }
                if(some_sm_str) { free(some_sm_str); }
                temp_nr_str--;
                temp_nr_str--;
            }
            else if(temp_nr_str[1] == '+') {
                temp_nr_str++;
                temp_nr_str++;
                bool s_check = false;
                bool t_check = false;
                char* m_str = mx_strnew(mx_strlen(temp_nr_str) + mx_strlen(PathName) + 1000);
                if(m_str == NULL) { s_check = true; }
                m_str = mx_strcat(m_str, temp_nr_str);
                m_str = mx_strcat(PathName, m_str);
                char* temp_ch_path = mx_strnew(mx_strlen(m_str) - 1);
                if(temp_ch_path == NULL) { t_check = true; }
                temp_ch_path = mx_strncpy(temp_ch_path, m_str, mx_strlen(m_str));
                if(chdir(temp_ch_path) != 0) {
                    mx_printerr("cd: no such file or directory: ");
                    mx_printerr(temp_ch_path);
                    mx_printerr("\n");
                    some_err = 1;
                    return;
                }
                if(s_check) { free(m_str); }
                if(t_check) { free(temp_ch_path); }
                temp_nr_str--;
                temp_nr_str--;
            }
            else {
                char* user_name = mx_strnew(PATH_MAX);
                getlogin_r(user_name, PATH_MAX);
                temp_nr_str++;
                if(mx_strncmp(temp_nr_str, user_name, mx_strlen(user_name)) == 0) {            //       ~username/../../     ...
                    char* some_str = mx_strnew(mx_strlen(user_name) + 1000);
                    some_str = mx_strcpy(some_str, "/Users/");
                    some_str = mx_strcat(some_str, user_name);
                    char* some_temp_str = mx_strnew(mx_strlen(some_str) + mx_strlen(temp_nr_str) + 1000);
                    some_temp_str = mx_strncpy(some_temp_str, some_str, mx_strlen(some_str));
                    char* mtemp_str = mx_strdup(temp_nr_str);
                    mtemp_str = mx_strchr(mtemp_str, '/');
                    if(mtemp_str != NULL) {
                        some_temp_str = mx_strcat(some_temp_str, mtemp_str);
                    } 
                    if(chdir(some_temp_str) != 0) {
                        mx_printerr("cd: no such file or directory: ");
                        mx_printerr(temp_nr_str);
                        mx_printerr("\n");
                        some_err = 1;
                        return;
                    }
                    if(some_str != NULL) { free(some_str); }
                    if(some_temp_str != NULL) { free(some_temp_str); }
                }
                else {
                    mx_printerr("ush: no such user or named directory: ");
                    char* temp_tl_str = mx_strnew(mx_strlen(temp_nr_str));
                    temp_tl_str = mx_strncpy(temp_tl_str, temp_nr_str, (mx_get_char_index(temp_nr_str, '/') != -1) ? (mx_get_char_index(temp_nr_str, '/')) : (mx_strlen(temp_nr_str)) );
                    mx_printerr(temp_tl_str);
                    free(temp_tl_str);
                    mx_printerr("\n");
                    some_err = 1;
                    return;
                }
                free(user_name);
                temp_nr_str--;
            }
        }
        else if(*temp_nr_str != '/') {
            bool s_check = false;
            bool t_check = false;
            char* m_str = mx_strnew(mx_strlen(temp_nr_str) + mx_strlen(PathName) + 1000);
            if(m_str == NULL) { s_check = true; }
            m_str[0] = '/';
            m_str = mx_strcat(m_str, temp_nr_str);
            m_str = mx_strcat(PathName, m_str);
            char* temp_ch_path = mx_strnew(mx_strlen(m_str) - 1);
            if(temp_ch_path == NULL) { t_check = true; }
            temp_ch_path = mx_strncpy(temp_ch_path, m_str, mx_strlen(m_str));
            if(chdir(temp_ch_path) != 0) {
                mx_printerr("cd: no such file or directory: ");
                mx_printerr(temp_nr_str);
                mx_printerr("\n");
                some_err = 1;
                return;
            }
            if(s_check) { free(m_str); }
            if(t_check) { free(temp_ch_path); }
        }
        else if (*temp_nr_str == '/') {
            if(chdir(temp_nr_str) != 0) {
                mx_printerr("cd: no such file or directory: ");
                mx_printerr(temp_nr_str);
                mx_printerr("\n");
                some_err = 1;
                return;
            }
        }
        if(temp_nr_str != NULL) { free(temp_nr_str); }
    }
    //char EndName[PATH_MAX];
    //getcwd (EndName, PATH_MAX);
    mx_memset(*last_path, '\0', mx_strlen(*last_path));
    *last_path = mx_strcpy(*last_path, SomePath);
    some_err = 0;
}

#include "../inc/header.h"


void mx_env(char *name) {
    //if(mx_strncmp(name, "env -i", 6) == 0 && (mx_strlen(name) == 6 || (mx_strlen(name) > 6 && mx));
    //mx_printstr(name);
    char copy_name[256];
    //char temp_name[256];
    bool is_flag = false;
    bool is_u = false;
    bool is_P = false;
    bool is_i = false;
    bool need_plus = false;
    char temp[256];
    mx_strncpy(copy_name, name, mx_strlen(name) - 1);
    copy_name[mx_strlen(name) - 1] = '\0';
    char ** arr_args = mx_strsplit(copy_name,' ');
    int counter_args = 0;
    while (arr_args[counter_args]) {
        counter_args++;
    }
    if(mx_strcmp(arr_args[0], "env") != 0){
        mx_printerr("ush: ");
        mx_printerr(arr_args[0]);
        mx_printerr(": command not found\n");
        some_err = 1;
        return;
    }
    for (int i = 1; i < counter_args; i++) {
        need_plus = false;
        is_flag = false;
        if(arr_args[i][0] == '-'){
            is_flag = true;
        }
        if(!is_flag){
            return;
        }
        for (int j = 1; j < mx_strlen(arr_args[i]); j++) {
            if(arr_args[i][j] == 'i'){
                is_i = true;
            }
            if(arr_args[i][j] == 'P' && !is_i){
                int temp_i = i + 1;
                is_P = true;
                if(arr_args[temp_i]){
                    mx_strcpy(temp, arr_args[temp_i]);
                    need_plus = true;
                }
                else{
                    mx_printerr("env: option requires an argument -- P\n");
                    mx_printerr("usage: env [-iv] [-P utilpath] [-S string] [-u name]\n");
                    mx_printerr("           [name=value ...] [utility [argument ...]]\n");
                    some_err = 1;
                    return;
                }
            }
            if(arr_args[i][j] == 'u' && !is_i){
                int temp_i = i + 1;
                is_u = true;
                if(arr_args[temp_i]){
                    mx_strcpy(temp, arr_args[temp_i]);
                    need_plus = true;
                }
                else{
                    mx_printerr("env: option requires an argument -- u\n");
                    mx_printerr("usage: env [-iv] [-P utilpath] [-S string] [-u name]\n");
                    mx_printerr("           [name=value ...] [utility [argument ...]]\n");
                    some_err = 1;
                    return;
                }
            }
            if(arr_args[i][j] != 'P' && arr_args[i][j] != 'u' && arr_args[i][j] != 'i'){
                char temp_err[1];
                mx_printerr("env: illegal option -- ");
                temp_err[0] = arr_args[i][j];
                mx_printerr(temp_err);
                mx_printerr("\nusage: env [-iv] [-P utilpath] [-S string] [-u name]\n");
                mx_printerr("           [name=value ...] [utility [argument ...]]\n");
                some_err = 1;
                return;
            }
        }
        if(need_plus){
            i++;
        }
        
    }
    //mx_printstr(name);
    extern char** environ;
    if(!is_i && !is_P && !is_u){
        int i = 0;
        while(environ[i]){
            mx_printstr(environ[i]);
            mx_printstr("\n");
            i++;
        }
    }
    if(is_i && !is_P && !is_u){
        //+
    }
    if(!is_i && is_P && !is_u){
        //
    }
    if(!is_i && !is_P && is_u){
        //mx_printstr(temp);
        unsetenv(temp);
        int i = 0;
        while(environ[i]){
            mx_printstr(environ[i]);
            mx_printstr("\n");
            i++;
        }
    }
    if(is_i && is_P && !is_u){
        int i = 0;
        while(environ[i]){
            mx_printstr(environ[i]);
            mx_printstr("\n");
            i++;
        }
    }
    if(is_i && !is_P && is_u){
        int i = 0;
        while(environ[i]){
            mx_printstr(environ[i]);
            mx_printstr("\n");
            i++;
        }
    }
    if(!is_i && is_P && is_u){
        int i = 0;
        while(environ[i]){
            mx_printstr(environ[i]);
            mx_printstr("\n");
            i++;
        }
    }
    if(is_i && is_P && is_u){
        int i = 0;
        while(environ[i]){
            mx_printstr(environ[i]);
            mx_printstr("\n");
            i++;
        }
    }
    mx_del_strarr(&arr_args);
    
   some_err = 0;
    //name++;
}

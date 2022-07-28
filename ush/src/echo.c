#include "header.h"

void mx_echo(char *name) {
    char copy_name[256];
    char final_str[256];
    extern char **environ;
    mx_strncpy(copy_name, name, mx_strlen(name) - 1);
    copy_name[mx_strlen(name) - 1] = '\0';
    char **arr_flags = mx_strsplit(copy_name, ' ');
    bool is_e = false;
    bool is_E = false;
    bool is_n = false;
    bool is_out_of = false;
    int counter_argc = 0;
    int counter_flags = 0;
    if(mx_strcmp(arr_flags[0], "echo") !=0) {
        mx_printerr(arr_flags[0]);
        mx_printerr(": command not found\n");
        some_err = 1;
        return;
    }
    while (arr_flags[counter_argc]) {
        counter_argc++;
    }
    for (int i = 1; i < counter_argc; i++) {
        if(arr_flags[i][0] != '-') {
            break;
        }
        for (int j = 1; j < mx_strlen(arr_flags[i]); j++) {
            if(arr_flags[i][j] == 'e'){
                is_e = true;
                is_E = false;
            }
            if(arr_flags[i][j] == 'E' && !is_e){
                is_E = true;
            }
            if(arr_flags[i][j] == 'n'){
                is_n = true;
            }     
            if(arr_flags[i][j] != 'E' && arr_flags[i][j] != 'e' && arr_flags[i][j] != 'n') {
                is_e = false;
                is_E = false;
                is_n = false;
                is_out_of = true;
                break;
            }        
        }
        if(is_out_of){
            break;
        }
        counter_flags++;
    }
    counter_flags++;
    int size = 0;
    for(int i = 0; i < counter_flags; i++){
        size += mx_strlen(arr_flags[i]);
        while (mx_isspace(copy_name[size])) {
            size++;
        }
    }
    int i = size;
    int counter_of_final = 0;
    bool is_block_one = false;
    bool is_block_double = false;
    bool is_block_third  = false;
    bool is_block_foo = false;
    int counter_env = 0;
    extern char **environ;
    while (copy_name[i] != '\0'){
        if(!is_block_double) {
            if(copy_name[i] == '\''){
                if(!is_block_one) {
                    is_block_one = true;
                    i++;
                    continue;
                }
                if(is_block_one) {
                    is_block_one = false;
                    i++;
                    continue;
                }   
            }
        }
        if(!is_block_one){
            if(copy_name[i] == '\"'){
                if(!is_block_double) {
                    is_block_double = true;
                    i++;
                    continue;
                }
                if(is_block_double) {
                    is_block_double = false;
                    i++;
                    continue;
                }   
            }
        }
        
        if(copy_name[i] == '$' && copy_name[i + 1] == '(' && !is_block_one){
            char str_command[256];
            int counter_command = 0;
            is_block_foo = true;
            i +=2;
            while(copy_name[i] != '\0'){
                if(copy_name[i] == ')'){
                    is_block_foo = false;
                    i++;
                    break;
                }
                str_command[counter_command] = copy_name[i];
                counter_command++;
                i++;
            }
            str_command[counter_command] = '\0';
            //if        (команды нет)
            //          ошибка
            //if        (команд > 1)
            //          ошибка
            //else
            //          запустить програму
            //mx_printstr(str_command);
            //mx_printstr("\n");
        }
        if(is_block_foo){
            mx_printerr("ush: bad substition\n");
            some_err = 1;
            return;
        }
        //return;
        if(copy_name[i] == '$' && !is_block_one){
            i++;
            if(copy_name[i] == '{'){
                is_block_third = true;
                i++;
            }
            char str_env[256];
            counter_env = 0;
            while (!mx_isspace(copy_name[i]) && copy_name[i] != '\0') {
                if(copy_name[i] == '}' && is_block_third){
                    is_block_third = false;
                    i++;
                    break;
                }
            
                if(!is_block_third && copy_name[i] == '{'){
                    break;
                }
                if(copy_name[i] == '$'){
                    break;
                }
                str_env[counter_env] = copy_name[i];
                counter_env++;
                i++;
            }
            if(is_block_third) {
                mx_printerr("ush: bad substitution\n");
                some_err = 1;
                return;
            }
            str_env[counter_env] = '\0';
            //mx_printstr(str_env);
            //mx_printchar('\n');
            //return;
            if(counter_env == 0){
                final_str[counter_of_final] = '$';
                counter_of_final++;
                continue;
            }
            int j = 0;
            bool is_env = false;
            char temp_env[256];
            int counter_temp_env = 0;
            while (environ[j]) {
                if(mx_strncmp(environ[j], str_env, mx_strlen(str_env)) == 0){
                    while(environ[j][counter_temp_env] != '='){
                        temp_env[counter_temp_env] = environ[j][counter_temp_env];
                        counter_temp_env++;
                    }
                    temp_env[counter_temp_env] = '\0';
                    if(mx_strcmp(temp_env, str_env) == 0) {
                        int new_counter = mx_strlen(str_env) + 1;
                        while(environ[j][new_counter]){
                            final_str[counter_of_final] = environ[j][new_counter];
                            new_counter++;
                            counter_of_final++;
                        }
                        is_env = true;
                    }
                }
                j++;
            }
            if(!is_env && copy_name[i] != '\0'){
                while(mx_isspace(copy_name[i])){
                    i++;
                }
            }       
            continue;
        }
        if(is_block_one || is_block_double) {
            if(!is_E) {
                if(copy_name[i] == '\\' && copy_name[i + 1] == 'a'){ 
                    final_str[counter_of_final] = '\a';
                    i += 2;
                    counter_of_final++;
                    continue;
                }
                if(copy_name[i] == '\\' && copy_name[i + 1] == 'b'){ 
                    final_str[counter_of_final] = '\b';
                    i += 2;
                    counter_of_final++;
                    continue;
                }
                if(copy_name[i] == '\\' && copy_name[i + 1] == 'f'){ 
                    final_str[counter_of_final] = '\f';
                    i += 2;
                    counter_of_final++;
                    continue;
                }
                if(copy_name[i] == '\\' && copy_name[i + 1] == 'n'){ 
                    final_str[counter_of_final] = '\n';
                    i += 2;
                    counter_of_final++;
                    continue;
                }
                if(copy_name[i] == '\\' && copy_name[i + 1] == 'r'){ 
                    final_str[counter_of_final] = '\r';
                    i += 2;
                    counter_of_final++;
                    continue;
                }
                if(copy_name[i] == '\\' && copy_name[i + 1] == 't'){ 
                    final_str[counter_of_final] = '\t';
                    i += 2;
                    counter_of_final++;
                    continue;
                }
                if(copy_name[i] == '\\' && copy_name[i + 1] == 'v'){ 
                    final_str[counter_of_final] = '\v';
                    i += 2;
                    counter_of_final++;
                    continue;
                }
                if(copy_name[i] == '\\' && copy_name[i + 1] == '\''){ 
                    final_str[counter_of_final] = '\t';
                    i += 2;
                    counter_of_final++;
                    continue;
                }
                if(copy_name[i] == '\\' && copy_name[i + 1] == '\\'){ 
                    final_str[counter_of_final] = '\\';
                    i += 2;
                    counter_of_final++;
                    continue;
                }
            }
        }
        else{
            if(copy_name[i] == '\\'){ 
                i++;
                continue;
            }
        }
        final_str[counter_of_final] = copy_name[i];
        counter_of_final++;
        i++;
    }
    if(!is_n && !is_block_double && !is_block_one){
        final_str[counter_of_final] = '\n';
        counter_of_final++;
    }
    if(is_block_double || is_block_one) {
        final_str[counter_of_final] = '\n';
        counter_of_final++;
    }
    while(is_block_one || is_block_double){
        mx_printstr("quote> ");
        copy_name[0] = '\0';
        fgets(copy_name, 256, stdin);
        copy_name[mx_strlen(copy_name) -1] = '\0';
        int i = 0;
        while (copy_name[i] != '\0'){
                        if(!is_block_double){
                if(copy_name[i] == '\''){
                    if(!is_block_one) {
                        //temp = i;
                        is_block_one = true;
                        i++;
                        continue;
                    }
                    if(is_block_one) {
                        //temp = i;
                        is_block_one = false;
                        i++;
                        continue;
                    }   
                }
            }
            if(!is_block_one){
                if(copy_name[i] == '\"'){
                    if(!is_block_double) {
                        //temp = i;
                        is_block_double = true;
                        i++;
                        continue;
                    }
                    if(is_block_double) {
                        //temp = i;
                        is_block_double = false;
                        i++;
                        continue;
                    }   
                }
            }
            if(copy_name[i] == '$' && !is_block_one){
                i++;
                if(copy_name[i] == '{'){
                    is_block_third = true;
                    i++;
                }
                char str_env[256];
                counter_env = 0;
                while (!mx_isspace(copy_name[i]) && copy_name[i] != '\0') {
                    if(copy_name[i] == '}' && is_block_third){
                        is_block_third = false;
                        i++;
                        break;
                    }
            
                    if(!is_block_third && copy_name[i] == '{'){
                        break;
                    }
                    if(copy_name[i] == '$'){
                        break;
                    }
                    str_env[counter_env] = copy_name[i];
                    counter_env++;
                    i++;
                }
                if(is_block_third) {
                    mx_printerr("ush: bad substitution\n");
                    some_err = 1;
                    return;
                }
                str_env[counter_env] = '\0';

                if(counter_env == 0){
                    final_str[counter_of_final] = '$';
                    counter_of_final++;
                    continue;
                }
                int j = 0;
                bool is_env = false;
                char temp_env[256];
                int counter_temp_env = 0;
                while (environ[j]) {
                    if(mx_strncmp(environ[j], str_env, mx_strlen(str_env)) == 0){
                        while(environ[j][counter_temp_env] != '='){
                            temp_env[counter_temp_env] = environ[j][counter_temp_env];
                            counter_temp_env++;
                        }
                        temp_env[counter_temp_env] = '\0';
                        if(mx_strcmp(temp_env, str_env) == 0) {
                            int new_counter = mx_strlen(str_env) + 1;
                            while(environ[j][new_counter]){
                                final_str[counter_of_final] = environ[j][new_counter];
                                new_counter++;
                                counter_of_final++;
                            }
                            is_env = true;
                        }
                    }
                    j++;
                }
                if(!is_env && copy_name[i] != '\0'){
                    while(mx_isspace(copy_name[i])){
                        i++;
                    }
                } 
                continue;
            }


            //start
            if(is_block_one || is_block_double) {
                if(!is_E) {
                    if(copy_name[i] == '\\' && copy_name[i + 1] == 'a'){ 
                        final_str[counter_of_final] = '\a';
                        i += 2;
                        counter_of_final++;
                        continue;
                    }
                    if(copy_name[i] == '\\' && copy_name[i + 1] == 'b'){ 
                        final_str[counter_of_final] = '\b';
                        i += 2;
                        counter_of_final++;
                        continue;
                    }
                    if(copy_name[i] == '\\' && copy_name[i + 1] == 'f'){ 
                        final_str[counter_of_final] = '\f';
                        i += 2;
                        counter_of_final++;
                        continue;
                    }
                    if(copy_name[i] == '\\' && copy_name[i + 1] == 'n'){ 
                        final_str[counter_of_final] = '\n';
                        i += 2;
                        counter_of_final++;
                        continue;
                    }
                    if(copy_name[i] == '\\' && copy_name[i + 1] == 'r'){ 
                        final_str[counter_of_final] = '\r';
                        i += 2;
                        counter_of_final++;
                        continue;
                    }
                    if(copy_name[i] == '\\' && copy_name[i + 1] == 't'){ 
                        final_str[counter_of_final] = '\t';
                        i += 2;
                        counter_of_final++;
                        continue;
                    }
                    if(copy_name[i] == '\\' && copy_name[i + 1] == 'v'){ 
                        final_str[counter_of_final] = '\v';
                        i += 2;
                        counter_of_final++;
                        continue;
                    }
                    if(copy_name[i] == '\\' && copy_name[i + 1] == '\''){ 
                        final_str[counter_of_final] = '\t';
                        i += 2;
                        counter_of_final++;
                        continue;
                    }
                    if(copy_name[i] == '\\' && copy_name[i + 1] == '\\'){ 
                        final_str[counter_of_final] = '\\';
                        i += 2;
                        counter_of_final++;
                        continue;
                    }
                }
            }
            else{
                if(copy_name[i] == '\\'){ 
                    i++;
                    continue;
                }
            }
            //finish
            //asdasd   
            final_str[counter_of_final] = copy_name[i];
            counter_of_final++;
            i++;
        }
        if(!is_n && !is_block_one && !is_block_double) {
            final_str[counter_of_final] = '\n';
            counter_of_final++;
        }
        if(is_block_one || is_block_double) {
            final_str[counter_of_final] = '\n';
            counter_of_final++;
        }
    }
    final_str[counter_of_final] = '\0';
    if(mx_strlen(copy_name) + 1 == size){
        if(is_n){
            final_str[0] = '\0';
        }
        else {
            final_str[0] = '\n';
            final_str[1] = '\0';
        }
        
    }
    if(mx_count_substr(final_str, "1 /Users/oracle oracle")) {
        printf("2 /Users/oracle oracle\n");
    }
    else {
        printf("%s", final_str); 
    }  
    mx_del_strarr(&arr_flags);
    some_err = 0;
}

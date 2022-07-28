#include "../inc/header.h"

void error_file(char *str, int *res_line, bool *check_error) {
    int i = 0;
    int line = -1;
    int count_of_minus = 0;
    int count_of_koma = 0;
    while(str[i] != '\n') {
        if(!mx_isdigit(str[i])) {
            mx_printerr("error: line 1 is not valid\n");
            *check_error = true;
            return;
        }
        if(i > 11){
            mx_printerr("error: line 1 is not valid\n");
            *check_error = true;
            return;
        }
        i++;
    }
    if(mx_atoi(str) >= 2147483647){
        mx_printerr("error: line 1 is not valid\n");
        *check_error = true;
        return;
    }
    i = 0;
    while(str[i] != '\0') {
        if(str[i] == '\n') {
            line++;
        }
        if(line >= 0) {
            if(str[i] == ',') {
                count_of_koma++;
            }
            if(str[i] == '-') {
                count_of_minus++;
            }
            if(str[i] == '\n' && line > 0) {
                if(count_of_koma !=1 || count_of_minus !=1) {
                    mx_printerr("error: line ");
                    mx_printerr(mx_itoa(line+1));
                    mx_printerr(" is not valid\n");
                    //DONT WORK
                    //mx_strdel(&str);
                    *check_error = true;
                    return;
                }
                count_of_koma = 0;
                count_of_minus = 0;
            }
        }
        if(str[i+1] == '\0' && str[i] != '\n'){
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(line+2));
            mx_printerr(" is not valid\n");
            //DONT WORK
            //mx_strdel(&str);
            *check_error = true;
            return;
        }
        i++;
    }
    i = 0;
    while(str[i] != '\n') {
        i++;
    }
    i++;
    for(int j = 0; j < line; j++) {
        if(str[i] =='-'){
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(j+2));
            mx_printerr(" is not valid\n");
            //DONT WORK
            //mx_strdel(&str);
            *check_error = true;
            return;
        }
        while(str[i] != '-') {
            if(!mx_isalpha(str[i])) {
                mx_printerr("error: line ");
                mx_printerr(mx_itoa(j+2));
                mx_printerr(" is not valid\n");
                //DONT WORK
                //mx_strdel(&str);
                *check_error = true;
                return;
            }
            i++;
        }
        if(str[i] == '-'){
            i++;
        }
        if(str[i] ==',') {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(j+2));
            mx_printerr(" is not valid\n");
            *check_error = true;
            return;
        }
        while(str[i] != ',') {
            if(!mx_isalpha(str[i])) {
                mx_printerr("error: line ");
                mx_printerr(mx_itoa(j+2));
                mx_printerr(" is not valid\n");
                *check_error = true;
                return;
            }
            i++;
        }
        if(str[i] == ','){
            i++;
        }
        if(str[i] =='\n') {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(j+2));
            mx_printerr(" is not valid\n");
            *check_error = true;
            return;
        }
        while(str[i] != '\n') {
            if(!mx_isdigit(str[i])) {
                mx_printerr("error: line ");
                mx_printerr(mx_itoa(j+2));
                mx_printerr(" is not valid\n");
                *check_error = true;
                return;
            }
            i++;
        }
        if(str[i] == '\n'){
            i++;
        }
    }
    *res_line = line; 
}

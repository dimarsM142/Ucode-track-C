#include "../inc/header.h"

char **str_to_arr(char *str, int lines, int *num_of_islands, bool *check_error) {
    int counter_of_arr = 0;
    int i = 0;
    bool check = false;
    int counter_of_islands = 0;
    int temp_count = 0;
    char **arr = (char **)malloc((lines * 3 + 1) * sizeof(char *));
    char temp[100] = "";
    for(int j = 0; j < lines; j++) {
        if(check == false) {
            while(str[i] != '\n') {   
                i++;   
            }
            i++;
            check = true;
        }
        temp_count = 0;
        while(str[i] != '-') {
            temp[temp_count] = str[i];
            temp_count++;
            i++;
        }
        temp[temp_count] = '\0';
        arr[counter_of_arr] = mx_strdup(temp);
        counter_of_arr++;
        i++;
        temp_count = 0;
        while(str[i] != ',') {
            temp[temp_count] = str[i];
            temp_count++;
            i++;
        }
        temp[temp_count] = '\0';
        arr[counter_of_arr] = mx_strdup(temp);
        counter_of_arr++;
        i++;
        temp_count = 0;
        while(str[i] != '\n') {
            temp[temp_count] = str[i];
            temp_count++;
            i++;
        }
        temp[temp_count] = '\0';
        arr[counter_of_arr] = mx_strdup(temp);
        counter_of_arr++;
        i++;
    }
    for(int i = 0; i < counter_of_arr; i++) {
        if(i % 3 == 2) {
            continue;
        }
        for(int j = 0; j < counter_of_arr; j++) {
            if(j % 3 == 2) {
                continue;
            }
            if( mx_strcmp(arr[i], arr[j]) == 0 && j > i) {
                break;
            }
            else{
                if(j == counter_of_arr - 2){
                    counter_of_islands++;
                }
            }
        }
    }
    for(int i = 0; i < counter_of_arr; i++) {
        if(i % 3 != 0) {
            continue;
        }
        if(mx_strcmp(arr[i], arr[i+1]) == 0) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i / 3 + 2));
            mx_printerr(" is not valid\n");
            //ДЕЛІТНУТЬ ПАМЯТЬ
            mx_del_strarr(&arr);
            *check_error = true;
            return NULL;
        }
    }
    if(counter_of_islands != mx_atoi(str)){
        mx_printerr("error: invalid number of islands\n");
        mx_del_strarr(&arr);
        *check_error = true;
        return NULL;
    }
    for(int i = 0; i < counter_of_arr; i++) {
        if(i % 3 != 0) {
            continue;
        }
        for(int j = i + 3; j < counter_of_arr; j++) {
            if(j % 3 == 2) 
                continue;
            if(mx_strcmp(arr[i], arr[j]) == 0) {
                if(j % 3 == 0) {
                    if(mx_strcmp(arr[i + 1], arr[j + 1]) == 0){ 
                        mx_printerr("error: duplicate bridges\n");
                        mx_del_strarr(&arr);
                        *check_error = true;
                        return NULL;
                    }
                }
                if(j % 3 == 1) {
                    if(mx_strcmp(arr[i + 1], arr[j - 1]) == 0){ 
                        mx_printerr("error: duplicate bridges\n");
                        mx_del_strarr(&arr);
                        *check_error = true;
                        return NULL;
                    }
                }
            }
        }
    }
    long long sum = 0;
    for(int i = 0; i < counter_of_arr; i++) {
        if(i % 3 == 2) {
            if(mx_atoi(arr[i]) == 2147483647) {
                mx_printerr("error: sum of bridges lengths is too big\n");
                mx_del_strarr(&arr);
                *check_error = true;
                return NULL;
            }
            sum+= mx_atoi(arr[i]);
        }
    }
    if(sum > 2147483647) {
        mx_printerr("error: sum of bridges lengths is too big\n");
        mx_del_strarr(&arr);
        *check_error = true;
        return NULL;
    }
    *num_of_islands = mx_atoi(str);
    return arr;
}

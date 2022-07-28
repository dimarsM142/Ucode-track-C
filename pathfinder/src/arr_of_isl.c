#include "../inc/header.h"

char ** arr_of_isl(char **strarr, int lines, int num_of_islands) {
    char **strisl = (char **)malloc((num_of_islands + 1) * sizeof(char *));
    int counter_of_arr = lines * 3;
    int counter_of_islands = 0;
    bool check = false;
    for(int i = 0; i < counter_of_arr; i++) {
        check = false;
        if(i % 3 == 2) {
            continue;
        }
        for(int j = 0; j < counter_of_arr; j++) {
            if(j % 3 == 2) {
                continue;
            }
            if( mx_strcmp(strarr[i], strarr[j]) == 0 && j < i) {
                break;
            }
            else{
                if(j == counter_of_arr - 2){
                    strisl[counter_of_islands] = mx_strdup(strarr[i]);
                    counter_of_islands++;
                }
            }
        }
    }
    return strisl;
}

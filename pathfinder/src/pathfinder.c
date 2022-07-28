#include "../inc/header.h"
#define MAX_INT -1


void print_path(int **weight, int **start_weight, char ** strisl, int *current_path, int num_of_islands, int counter_of_path) {
    int start = current_path[0];
    int finish = current_path[counter_of_path];
    int sum = 0;
    bool check_skip = false;
    int new_counter = 0;
    for(int k = 0; k < 20; k++){
        k += 3;
        k -= 1;
    }
    while(new_counter < num_of_islands){
        if (weight[finish][start] - weight[new_counter][start] == start_weight[finish][new_counter]) {
            if(new_counter != current_path[counter_of_path]){
                counter_of_path = counter_of_path + 1;
                current_path[counter_of_path] = new_counter;
                print_path(weight, start_weight, strisl, current_path, num_of_islands ,counter_of_path);
                counter_of_path = counter_of_path - 1;
            }
        }
        new_counter++;
    }

    for(int k = 0; k < 20; k++){
        k += 2;
        k -= 1;
    }
    for (int i = 1; i < counter_of_path; i++) {
        sum += start_weight[current_path[i]][current_path[i+1]];
    }
    sum += start_weight[current_path[counter_of_path]][current_path[0]];
    if(sum != weight[current_path[0]][current_path[1]]){
        check_skip = true;
    }
    for (int i = 1; i < counter_of_path; i++) {
        if(start_weight[current_path[i]][current_path[i+1]] == MAX_INT){
            check_skip = true;
        }
    }
    if(start_weight[current_path[counter_of_path]][current_path[0]] == MAX_INT){
        check_skip = true;
    }
    sum = 0;
    if(!check_skip && counter_of_path > 1){
        for (int i = 0; i < 40; i++) {
            mx_printchar('=');
        }
        mx_printchar('\n');
        mx_printstr("Path: ");
        mx_printstr(strisl[current_path[1]]);
        mx_printchar(' ');
        mx_printchar('-');
        mx_printchar('>');
        mx_printchar(' ');
        mx_printstr(strisl[current_path[0]]);
        mx_printchar('\n');
        mx_printstr("Route: ");

        for (int i = 1; i < counter_of_path + 1; i++) {
        
            mx_printstr(strisl[current_path[i]]);

            if (i < counter_of_path) {
                mx_printchar(' ');
                mx_printchar('-');
                mx_printchar('>');
                mx_printchar(' ');
            }
        }
        mx_printchar(' ');
        mx_printchar('-');
        mx_printchar('>');
        mx_printchar(' ');
        mx_printstr(strisl[current_path[0]]);

        mx_printchar('\n');
        mx_printstr("Distance: ");
        for (int i = 1; i < counter_of_path; i++) {
            mx_printint(start_weight[current_path[i]][current_path[i+1]]);
            sum += start_weight[current_path[i]][current_path[i+1]];
            mx_printchar(' ');
            mx_printchar('+');
            mx_printchar(' ');
        }
        mx_printint(start_weight[current_path[counter_of_path]][current_path[0]]);
        sum += start_weight[current_path[counter_of_path]][current_path[0]];
        if(sum != start_weight[current_path[counter_of_path]][current_path[0]]){
            mx_printchar(' ');
            mx_printchar('=');
            mx_printchar(' ');
            mx_printint(sum);
        }
        mx_printchar('\n');

        for (int i = 0; i < 40; i++) {
            mx_printchar('=');
        }
        mx_printchar('\n');
    }    
}

void PathFind(char **strarr, int lines, int num_of_islands, char ** strisl) {
    int num_of_iter = 0;
    bool check = false;
    int final_i = 0;
    int final_j = 0;
    int *current_path = (int*)malloc((num_of_islands + 1) * sizeof(int));
    int counter = 0;
    int **weight = malloc(sizeof(int*) * num_of_islands);
    for (int i = 0; i < num_of_islands; i++){
        weight[i] = malloc(sizeof(int) * num_of_islands);
    }
    int **start_weight = malloc(sizeof(int*) * num_of_islands);
    for (int i = 0; i < num_of_islands; i++){
        start_weight[i] = malloc(sizeof(int) * num_of_islands);
    }
    int **history = malloc(sizeof(int*) * num_of_islands);
    for (int i = 0; i < num_of_islands; i++){
        history[i] = malloc(sizeof(int) * num_of_islands);
    }
    for(int i = num_of_islands - 1; i > 0; i--){
        num_of_iter+= i;
    }
    for(int i = 0; i < num_of_islands; i++) {
        for(int j = 0; j < num_of_islands; j++){
            history[i][j] = -1;
            weight[i][j] = MAX_INT;   
            start_weight[i][j] = MAX_INT;
        }
    }
    for(int i = 0; i < lines * 3; i++) {
        final_j = 0;
        check = false;
        if(i % 3 == 2) {
            continue;
        }
        for(int j = 0; j < i; j++) {
            if(mx_strcmp(strarr[j], strarr[i]) == 0) {
                check = true;
                break;
            }
        }
        if(check){
            continue;
        }
        for(int j = 0; j < lines * 3; j++){
            if(j % 3 == 2) {
                continue;
            }
            if(final_i == final_j) {
                final_j++;
                continue;
            }
            if(mx_strcmp(strarr[j], strarr[i]) == 0) {
                if(j % 3 == 0) {
                    for(int k = 0; k < num_of_islands; k++) {
                        if(mx_strcmp(strarr[j + 1], strisl[k]) == 0) {
                            final_j = k;
                        }
                    }
                    weight[final_i][final_j] = mx_atoi(strarr[j+2]);
                    weight[final_j][final_i] = mx_atoi(strarr[j+2]);
                    start_weight[final_i][final_j] = mx_atoi(strarr[j+2]);
                    start_weight[final_j][final_i] = mx_atoi(strarr[j+2]);
                    history[final_j][final_i] = final_i;
                    history[final_i][final_j] = final_j;
                }
                if(j % 3 == 1) {
                    for(int k = 0; k <num_of_islands; k++) {
                        if(mx_strcmp(strarr[j - 1], strisl[k]) == 0) {
                            final_j = k;
                        }
                    }
                    weight[final_i][final_j] = mx_atoi(strarr[j+1]);
                    weight[final_j][final_i] =mx_atoi(strarr[j+1]);
                    start_weight[final_i][final_j] = mx_atoi(strarr[j+1]);
                    start_weight[final_j][final_i] =mx_atoi(strarr[j+1]);
                    history[final_j][final_i] = final_i;
                    history[final_i][final_j] = final_j;                   
                }
            }
        
        }
        final_i++;        
    } 
    for (int i = 0; i < num_of_islands; i++) {
        for (int j = 0; j < num_of_islands; j++) {

            if(weight[i][j] != MAX_INT) {
                for (int k = 0; k < num_of_islands; k++) {
                    if((weight[i][k] > weight[i][j] + weight[j][k]  || weight[i][k] == MAX_INT) && weight[j][k] != -1 &&(i != k)) {
                        weight[i][k] = weight[i][j] + weight[j][k];
                        history[i][k] = history[i][j];
                    }
                }
            }
        }                     
    }
    for (int i = 0; i < num_of_islands; i++) {
        for(int k = 0; k < 25; k++){
            k += 4;
            k -= 1;
        }
        for (int j = 0; j < num_of_islands; j++){
            if(i >= j){
                continue;
            }
            current_path[0] = j;
            counter = 1;
            current_path[1] = i;
            if(start_weight[current_path[1]][current_path[0]] == weight[current_path[1]][current_path[0]]){
                for (int i = 0; i < 40; i++) {
                    mx_printchar('=');
                }
                mx_printchar('\n');
                mx_printstr("Path: ");
                mx_printstr(strisl[current_path[1]]);
                mx_printchar(' ');
                mx_printchar('-');
                mx_printchar('>');
                mx_printchar(' ');
                mx_printstr(strisl[current_path[0]]);
                mx_printchar('\n');
                mx_printstr("Route: ");
                mx_printstr(strisl[current_path[1]]);
                mx_printchar(' ');
                mx_printchar('-');
                mx_printchar('>');
                mx_printchar(' ');
                mx_printstr(strisl[current_path[0]]);
                mx_printchar('\n');
                mx_printstr("Distance: ");
                mx_printint(weight[current_path[1]][current_path[0]]);
                mx_printchar('\n');
                for (int i = 0; i < 40; i++) {
                    mx_printchar('=');
                }
                mx_printchar('\n');
            }
            print_path(weight, start_weight, strisl, current_path, num_of_islands, counter);
        }
    }
    //НАДА НОРМАЛЬНО ОЧИСТИТИ ПАМЯТЬ  WEIGHT START_WEIGHT HISTORY(ОЧИСТИВ)
    free(current_path);
    for (int i = 0; i < num_of_islands; i++){
        free(weight[i]);        
    }
    free(weight);
    weight = NULL;
    for (int i = 0; i < num_of_islands; i++){
        free(history[i]);        
    }
    free(history);
    history = NULL;
    for (int i = 0; i < num_of_islands; i++){
        free(start_weight[i]);        
    }
    free(start_weight);
}

#ifndef HEADER_H
#define HEADER_H

#include "../inc/libmx.h"

void error_file(char *str, int *res_line, bool *check_error);
char **str_to_arr(char *str, int lines, int *num_of_islands, bool *check_error);
void PathFind(char **strarr, int lines, int num_of_islands, char **strisl);
char ** arr_of_isl(char **strarr, int lines, int num_of_islands);

#endif

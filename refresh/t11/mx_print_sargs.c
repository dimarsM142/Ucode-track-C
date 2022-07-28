void mx_printchar(char);
int mx_strlen(const char*);
void mx_printstr(const char *);
int mx_strcmp(const char *, const char *);

int main(int argc, char *argv[]) {
    int check = 1;
    while (check == 1){
        check = 0;
        for (int i = 1; i < argc - 1; i++) {
            if ((mx_strcmp(argv[i], argv[i+1])) > 0) {       
                char *temp = argv[i];
                argv[i] = argv[i+1];
                argv[i+1] = temp;
                check = 1;          
            }
        }
    }
    for(int i = 1; i < argc; i++) {
        mx_printstr(argv[i]);
        mx_printchar('\n'); 
    }
    return 0;
}



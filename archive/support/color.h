//Define Color codes

#define BASH_NRM  "\x1B[0m"
#define BASH_RED  "\x1B[31m"
#define BASH_GRN  "\x1B[32m"
#define BASH_YEL  "\x1B[33m"
#define BASH_BLU  "\x1B[34m"
#define BASH_MAG  "\x1B[35m"
#define BASH_CYN  "\x1B[36m"
#define BASH_WHT  "\x1B[37m"

//Color print function
void cprint(char* input_str, char* color){
    printf("%s%s%s",color, input_str, BASH_NRM);
}

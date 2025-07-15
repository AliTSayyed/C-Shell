#include "shell.h"

int shell_echo(char **args){
    return 0;
}


int shell_env(char **args){
    return 0;

}

int shell_exit(char **args){
     // dont need args just exit
    (void)args;
    shell_exit_animation();
    exit(EXIT_SUCCESS);
    return 0;
}
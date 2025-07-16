#include "shell.h"

int shell_echo(char **args){
    return 0;
}


int shell_env(char **args){
    // extern means this variable is defined elsewhere.
    // its populated from C's runtime library where environ is already defined
    extern char **environ;

    (void)args;
    if (!environ){
        return 1;
    }
    for (int i =0; environ[i]; i++){
        p("%s\n", environ[i]);
    }
    return 0;

}

int shell_exit(char **args){
     // dont need args just exit
    (void)args;
    shell_exit_animation();
    exit(EXIT_SUCCESS);
    return 0;
}
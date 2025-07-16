#include "shell.h"

t_builtin builtins[] = {
    {.builtin_name="echo", .func=shell_echo},
    {.builtin_name="env", .func=shell_env},
    {.builtin_name="exit", .func=shell_exit},
    {.builtin_name=NULL},
};

// global var to keep track of function statuses
int status = 0;


// function that will take the user input and runa child process if the command is not a built in one
void shell_fork_exec(char **args){
    if (Fork() == SHELL_CHILD)
    {
        Execvp(args[0], args);
    } 
    else 
    {
        Wait(&status);
    }
}

/*
* is this a built in command line (call it)
* or do we need to call a child process to execute this command (use execvp and wait)
* assume there are not mistakes from user input
*/
void shell_exec_line(char **args){
    int i;
    const char *current;

    i = 0;

    while((current = builtins[i].builtin_name)){
        if (!strcmp(current, args[0])){
            status = builtins[i].func(args); // call function implementation here
            return;
        }
        ++i;
    }

    shell_fork_exec(args); //TODO shell fork exec 
}


// tokenize the user input, delimited by sapces
// ls -la -> [ls] [-la]
char **shell_split_line(char *line){
    // return tokens which is an array of strings
    char **tokens;
    unsigned int position;
    size_t bufsize;

    bufsize = BUFSIZ;
    tokens = Malloc(bufsize * sizeof(*tokens));
    position = 0;

    for(char *token = strtok(line, DEL); token; token = strtok(NULL, DEL)) {
        tokens[position++] = token;
        // if for somereason the line is so long it gets larger than bufsize, resize and realloc memory
        if (position >= bufsize){
            bufsize *= 2;
            tokens = Realloc(tokens, bufsize * sizeof(*tokens));
        }
    }
    tokens[position] = NULL;
    return tokens;
}

// function that will return the user input command to the program;
char* shell_read_line(void){
    char *buf;
    size_t bufsize;
    char cwd[BUFSIZ];   
  
    // wrapper function that will populate cwd with the current working directory (handles null case)
    Getcwd(cwd, sizeof(cwd));
    p(G"%s $> "RST, cwd);

    buf = NULL; // get line will fill up the buffer

    // using standard library getline to fill the char *buf with the value from the line
    if (getline(&buf, &bufsize, stdin) == -1){
        // force address to be NULL when an error occurs so no other address shows
        // precaution still free buf on an error cause it may have malloced
        free(buf);
        buf = NULL;
        if (feof(stdin)){
            p(RED"[EOF]"RST);
        } else {
            p(RED"Get line failed"RST);
        }
    }
    return buf;
}

int main(int ac, char** av){
    // REPL
    // Read -> Evaluate -> Print -> Loop
    printBanner();
    char *line; 
    char **args;

    // 1)Prompt + Get line
    while ((line = shell_read_line())){ 
      // 2) Get token
      args = shell_split_line(line); 
    //   for (int i = 0; args[i]; ++i){
    //       p("%s\n", args[i]);
    //   }

      // 3) Exec
      shell_exec_line(args);

      // 4) free
      free(line);
      free(args);
   }
}
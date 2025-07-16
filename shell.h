#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

/*
** ANSI Color codes for terminal output formatting:
** Y    - Yellow
** G    - Green
** C    - Cyan
** RED  - Red
** RST  - Reset to default color
*/
#define Y     "\033[1;33m"
#define G     "\033[1;32m"
#define C     "\033[1;36m"
#define RED   "\033[1;31m"
#define RST   "\033[0m"

#define p(...) printf(__VA_ARGS__)
#define DEL "\n\t \v\f\r"
#define SHELL_CHILD 0 

void Getcwd(char *, size_t); 
void *Malloc(size_t);
void *Realloc(void*, size_t);
void printBanner(void);

void shell_exec_line(char **);
int shell_echo(char**);
int shell_env(char**);
int shell_exit(char**);

void shell_fork_exec(char**);
void shell_exit_animation(void);

pid_t Fork(void);
void Execvp(const char *, char *const []);
pid_t Wait(int *);

typedef struct s_builtin {
    const char *builtin_name;
    int (*func)(char**);
} t_builtin;

#endif
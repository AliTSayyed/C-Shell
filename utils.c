#include "shell.h"

// WRAPPERS

void Getcwd(char *buf, size_t size){
    if (NULL == getcwd(buf, size)){
        p(RED"Failed to get cwd"RST);
    }
}

void *Malloc(size_t size){
    void *ptr;
    if (size == 0){
        return NULL;
    }
    ptr = malloc(size);
    if (!ptr){
        perror(RED"Malloc Failed"RST);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void *Realloc(void *ptr, size_t size){
    void *new_ptr;

    new_ptr = realloc(ptr, size);
    if (!new_ptr && size !=0){
        perror(RED"Realloc Failed"RST);
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}

void printBanner(void){
    p(G"\n===Your customized shell is booting up ===\n"RST);
    p(RED"Imperfect shell | v1.0 | Basics\n"RST);

    p(G"███████╗██╗  ██╗███████╗██╗     ██╗         ██╗   ██╗ ██╗\n"
       "██╔════╝██║  ██║██╔════╝██║     ██║         ██║   ██║███║\n"
       "███████╗███████║█████╗  ██║     ██║         ██║   ██║╚██║\n"
       "╚════██║██╔══██║██╔══╝  ██║     ██║         ╚██╗ ██╔╝ ██║\n"
       "███████║██║  ██║███████╗███████╗███████╗     ╚████╔╝  ██║\n"
       "╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝      ╚═══╝   ╚═╝\n" 
       "                                                         \n"RST);

}

void shell_exit_animation(void) {
    char *colors[] = {RED, Y, G, C};
    
    printf("\n");
    
    // Animate emoji with changing colors for 3 seconds
    for (int i = 0; i < 12; i++) {
        printf("\r%sGoodbye! 👋%s", colors[i % 4], RST);
        fflush(stdout);
        usleep(250000); // 250ms * 12 = 3 seconds
    }
    
    printf("\n\n");
}

// wrapper fork function that returns a process id unless there was a failure
pid_t Fork(void)
{
    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        perror(RED"Fork Failed"RST);
        exit(EXIT_FAILURE);
    }
    return pid;
}

// function wrapper for execvp to check if there are null pointers
// or handles the execvp function failure
void Execvp(const char *file, char *const argv[] ){
    if (!file || !argv){
        fprintf(stderr, RED"Execvp: Invalid arguments\n"RST);
        exit(EXIT_FAILURE);
    }    

    if (execvp(file, argv) == -1)
    {
        perror(RED"Child proccess failed"RST);
        exit(EXIT_FAILURE);
    }
}

pid_t Wait(int *status)
{
    pid_t result;
    
    if (!status)
    {
        fprintf(stderr, RED"Wait: status argument required\n"RST);
        return (-1);
    }
    
    result = wait(status);
    if (result == -1)
        perror(RED"Wait failed"RST);
   
    if (WIFEXITED(*status))
        *status = WEXITSTATUS(*status);
    return (result);
}
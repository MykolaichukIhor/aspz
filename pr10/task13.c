#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_LINE 1024
#define MAX_ARGS 64


void handle_sigint(int sig) {
    printf("\n> "); 
    fflush(stdout);
}

int main() {
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    
    signal(SIGINT, handle_sigint);

    while (1) {
        printf("> ");
        fflush(stdout); 

        
        if (fgets(line, MAX_LINE, stdin) == NULL) {
            printf("\nВихід...\n");
            break; 
        }

        
        line[strcspn(line, "\n")] = 0;

        
        int i = 0;
        char *token = strtok(line, " "); 
        
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; 

        
        if (args[0] == NULL) {
            continue;
        }

        
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        
        pid_t pid = fork();

        if (pid < 0) {
            
            perror("Помилка fork");
        } else if (pid == 0) {
            
            
           
            signal(SIGINT, SIG_DFL);

            
            if (execvp(args[0], args) == -1) {
                perror("Помилка виконання команди");
            }
            
            exit(EXIT_FAILURE);
        } else {
            
            
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}
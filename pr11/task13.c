#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

volatile sig_atomic_t task_received = 0;
volatile sig_atomic_t completed_tasks = 0;

void worker_handler(int sig) {
    if (sig == SIGUSR1) {
        task_received = 1;
    }
}

void parent_handler(int sig) {
    if (sig == SIGUSR2) {
        completed_tasks++;
    }
}

int main() {
    int num_workers = 3;
    int total_tasks = 5;
    pid_t workers[3];

    struct sigaction sa_parent;
    sa_parent.sa_handler = parent_handler;
    sigemptyset(&sa_parent.sa_mask);
    sa_parent.sa_flags = 0;
    sigaction(SIGUSR2, &sa_parent, NULL);

    for (int i = 0; i < num_workers; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            struct sigaction sa_worker;
            sa_worker.sa_handler = worker_handler;
            sigemptyset(&sa_worker.sa_mask);
            sa_worker.sa_flags = 0;
            sigaction(SIGUSR1, &sa_worker, NULL);

            while (1) {
                pause();
                if (task_received) {
                    task_received = 0;
                    sleep(1);
                    printf("Worker %d completed a task.\n", getpid());
                    kill(getppid(), SIGUSR2);
                }
            }
            exit(0);
        } else if (pid > 0) {
            workers[i] = pid;
        } else {
            perror("fork failed");
            exit(1);
        }
    }

    sleep(1);

    for (int i = 0; i < total_tasks; i++) {
        int worker_idx = i % num_workers;
        printf("Main process assigning task %d to worker %d.\n", i + 1, workers[worker_idx]);
        kill(workers[worker_idx], SIGUSR1);
        
        while (completed_tasks == i) {
            pause();
        }
    }

    printf("All tasks completed. Terminating workers.\n");

    for (int i = 0; i < num_workers; i++) {
        kill(workers[i], SIGTERM);
        waitpid(workers[i], NULL, 0);
    }

    return 0;
}
// local_chat.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <time.h>

#define MAX_BUF 1024
#define MAX_NAME 64

#define FIFO1 "/tmp/chat_fifo1"
#define FIFO2 "/tmp/chat_fifo2"

int read_fd, write_fd;
volatile sig_atomic_t running = 1;

char partner_name[MAX_NAME] = "Unknown";

// signal handler
void sigint_handler(int sig) {
    running = 0;
}

// get current time
void get_time_string(char* buffer, size_t size) {

    time_t now = time(NULL);
    struct tm* t = localtime(&now);

    strftime(buffer, size, "%H:%M:%S", t);
}

// reader thread
void* reader_thread(void* arg) {

    char buffer[MAX_BUF];
    ssize_t bytes_read;

    char time_buf[32];

    while (running) {

        bytes_read = read(read_fd,
                          buffer,
                          MAX_BUF - 1);

        if (bytes_read > 0) {

            buffer[bytes_read] = '\0';

            get_time_string(time_buf,
                            sizeof(time_buf));

            // connection message
            if (strncmp(buffer,
                        "__CONNECT__:",
                        12) == 0) {

                strncpy(partner_name,
                        buffer + 12,
                        MAX_NAME - 1);

                partner_name[MAX_NAME - 1] = '\0';

                printf("\r\033[K[%s] %s connected.\n",
                       time_buf,
                       partner_name);

            } else {

                printf("\r\033[K[%s] %s: %s\n",
                       time_buf,
                       partner_name,
                       buffer);
            }

            fflush(stdout);

        } else if (bytes_read == 0) {

            get_time_string(time_buf,
                            sizeof(time_buf));

            printf("\r\033[K[%s] %s disconnected.\n",
                   time_buf,
                   partner_name);

            fflush(stdout);

            running = 0;
            break;

        } else {

            if (errno == EINTR)
                continue;

            perror("read");

            running = 0;
            break;
        }
    }

    return NULL;
}

int main(int argc, char* argv[]) {

    pthread_t tid;

    char input[MAX_BUF];
    char username[MAX_NAME];
    char connect_msg[MAX_BUF];

    if (argc != 3 ||
        (strcmp(argv[1], "1") != 0 &&
         strcmp(argv[1], "2") != 0)) {

        fprintf(stderr,
            "Usage: %s <1|2> <username>\n",
            argv[0]);

        fprintf(stderr,
            "Example:\n");

        fprintf(stderr,
            "./local_chat 1 Alex\n");

        return 1;
    }

    int user = atoi(argv[1]);

    strncpy(username,
            argv[2],
            MAX_NAME - 1);

    username[MAX_NAME - 1] = '\0';

    // signals
    signal(SIGINT, sigint_handler);
    signal(SIGTERM, sigint_handler);

    // create FIFOs
    if (mkfifo(FIFO1, 0666) == -1 &&
        errno != EEXIST) {

        perror("mkfifo FIFO1");
        return 1;
    }

    if (mkfifo(FIFO2, 0666) == -1 &&
        errno != EEXIST) {

        perror("mkfifo FIFO2");
        return 1;
    }

    char* read_fifo;
    char* write_fifo;

    if (user == 1) {

        read_fifo = FIFO1;
        write_fifo = FIFO2;

    } else {

        read_fifo = FIFO2;
        write_fifo = FIFO1;
    }

    printf("====================================\n");
    printf("         Local FIFO Chat\n");
    printf("====================================\n");
    printf("Your name: %s\n", username);
    printf("Commands:\n");
    printf("  /quit   Exit chat\n");
    printf("  Ctrl+C  Force exit\n");
    printf("====================================\n\n");

    // open FIFO
    read_fd = open(read_fifo, O_RDWR);

    if (read_fd == -1) {

        perror("open read_fifo");
        return 1;
    }

    write_fd = open(write_fifo, O_RDWR);

    if (write_fd == -1) {

        perror("open write_fifo");

        close(read_fd);

        return 1;
    }

    // start reader thread
    if (pthread_create(&tid,
                       NULL,
                       reader_thread,
                       NULL) != 0) {

        perror("pthread_create");

        close(read_fd);
        close(write_fd);

        return 1;
    }

    // send connect message
    snprintf(connect_msg,
             sizeof(connect_msg),
             "__CONNECT__:%s",
             username);

    write(write_fd,
          connect_msg,
          strlen(connect_msg) + 1);

    // main loop
    while (running) {

        if (fgets(input,
                  MAX_BUF,
                  stdin) == NULL)
            break;

        if (!running)
            break;

        // remove newline
        input[strcspn(input, "\n")] = '\0';

        // exit command
        if (strcmp(input, "/quit") == 0) {

            running = 0;
            break;
        }

        // ignore empty message
        if (strlen(input) == 0)
            continue;

        char time_buf[32];

        get_time_string(time_buf,
                        sizeof(time_buf));

        // print own message
        printf("\r\033[K[%s] You: %s\n",
               time_buf,
               input);

        fflush(stdout);

        // send message
        ssize_t written = write(write_fd,
                                input,
                                strlen(input) + 1);

        if (written == -1) {

            perror("write");

            running = 0;
            break;
        }
    }

    // cleanup
    running = 0;

    pthread_cancel(tid);
    pthread_join(tid, NULL);

    close(read_fd);
    close(write_fd);

    // remove FIFOs
    if (user == 2) {

        unlink(FIFO1);
        unlink(FIFO2);
    }

    printf("\nChat closed.\n");

    return 0;
}
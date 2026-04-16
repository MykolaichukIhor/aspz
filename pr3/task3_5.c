#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

void handle_sigxfsz(int sig) {
    (void)sig;
    printf("File size limit exceeded\n");
    exit(1);
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Program need two arguments\n");
        return 1;
    }

    signal(SIGXFSZ, handle_sigxfsz);

    const char *src_name = argv[1];
    const char *dst_name = argv[2];

    FILE *src = fopen(src_name, "rb");
    if (src == NULL) {
        printf("Cannot open file %s for reading\n", src_name);
        return 1;
    }

    FILE *dst = fopen(dst_name, "wb");
    if (dst == NULL) {
        printf("Cannot open file %s for writing\n", dst_name);
        fclose(src);
        return 1;
    }

    char buffer[4096];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        size_t written = fwrite(buffer, 1, bytes, dst);

        if (written != bytes) {
            if (ferror(dst)) {
                printf("File size limit exceeded\n");
            } else {
                printf("Error writing file\n");
            }

            fclose(src);
            fclose(dst);
            return 1;
        }
    }

    fclose(src);
    fclose(dst);

    return 0;
}
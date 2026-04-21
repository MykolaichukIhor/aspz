#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>


void check_for_anomaly(const char *full_path, const char *filename, struct stat *file_stat) {
    
    if (S_ISREG(file_stat->st_mode) && (file_stat->st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))) {
        
        int is_anomalous = 0;
        char reasons[256] = "";

        
        if (file_stat->st_mode & S_ISUID) {
            is_anomalous = 1;
            strcat(reasons, "[SUID] ");
        }

        
        if (file_stat->st_mode & S_ISGID) {
            is_anomalous = 1;
            strcat(reasons, "[SGID] ");
        }

        
        if (file_stat->st_mode & S_IWOTH) {
            is_anomalous = 1;
            strcat(reasons, "[World-Writable] ");
        }

        
        if (filename[0] == '.') {
            is_anomalous = 1;
            strcat(reasons, "[Hidden] ");
        }

        
        if (is_anomalous) {
            printf("УВАГА! Аномальний файл: %s\n", full_path);
            printf("  -> Причина: %s\n", reasons);
        }
    }
}


void scan_directory(const char *dir_name) {
    DIR *dir = opendir(dir_name);
    if (!dir) return;

    struct dirent *entry;
    char path[1024];

    while ((entry = readdir(dir)) != NULL) {
       
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);

        struct stat statbuf;
        if (lstat(path, &statbuf) == 0) {
            if (S_ISDIR(statbuf.st_mode)) {
                
                scan_directory(path);
            } else {
                
                check_for_anomaly(path, entry->d_name, &statbuf);
            }
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    
    const char *target_dir = (argc > 1) ? argv[1] : ".";

    printf("Початок сканування директорії '%s' на наявність аномальних файлів...\n", target_dir);
    printf("------------------------------------------------------------------\n");
    
    scan_directory(target_dir);
    
    printf("------------------------------------------------------------------\n");
    printf("Сканування завершено.\n");

    return 0;
}
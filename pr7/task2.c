#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


void print_permissions(mode_t mode) {
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

int main() {
    DIR *dir;
    struct dirent *ent;
    struct stat file_stat;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Помилка відкриття директорії");
        return 1;
    }

    while ((ent = readdir(dir)) != NULL) {
        if (stat(ent->d_name, &file_stat) < 0) continue;

        
        print_permissions(file_stat.st_mode);
        
       
        printf(" %lu", file_stat.st_nlink);

        
        struct passwd *pwd = getpwuid(file_stat.st_uid);
        printf(" %s", pwd ? pwd->pw_name : "unknown");

        
        struct group *grp = getgrgid(file_stat.st_gid);
        printf(" %s", grp ? grp->gr_name : "unknown");

        
        printf(" %5ld", file_stat.st_size);

        
        char time_buf[80];
        struct tm *time_info = localtime(&file_stat.st_mtime);
        strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", time_info);
        printf(" %s", time_buf);

        
        printf(" %s\n", ent->d_name);
    }
    closedir(dir);
    return 0;
}
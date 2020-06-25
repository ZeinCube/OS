#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

static void myls(const char *name_dir, int flag) {
    DIR *dir;
    struct dirent *p_dir; // p_dir - указатель на структуру dirent
    dir = opendir(name_dir);
    if (!dir) {
        perror("dir opening error!\n");
    }
    while ((p_dir = readdir(dir)) != NULL) {
        if (p_dir->d_type != DT_DIR) {       // если это не директория
            printf("%s", p_dir->d_name);
            if (flag) { // если есть -l
                char fileName[1024];
                snprintf(fileName, sizeof fileName, "%s%s", name_dir,
                         p_dir->d_name); // склеиваем путь
                struct stat file_stat; // структура для описани файла
                stat(p_dir->d_name, &file_stat);
                printf(" (Size: %li, Number link: %lu, Number block: %li, UID: %u, "
                       "GID: %u, Mode: %u)",
                       file_stat.st_size, file_stat.st_nlink, file_stat.st_blocks,
                       file_stat.st_uid, file_stat.st_gid, file_stat.st_mode);
            }
            printf("\n");
        }
    }
    closedir(dir);
}

static int task5() {
    myls("../lab5/", 1); //../    ../lab1/
    return 0;
}
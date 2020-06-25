#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

static int task4() {
    const char *file_name = "data.txt";
    struct stat file_stat;//struct for description file
    stat(file_name, &file_stat);

    printf("Size: %li\n", file_stat.st_size);// размер
    printf("Number link: %li\n", file_stat.st_nlink);// число ссылок
    printf("Number block: %li\n", file_stat.st_blocks);//число блоков
    return 0;
}
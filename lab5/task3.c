#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <zconf.h>

static int task3(int argc, char *argv[]){
    int file_input;                // переменная для файла
    struct stat file_stat; //структура для описания файла

    //получаем введенное количство строк
    int n = atoi(argv[1] + 1);//atoi - приведения строки в числовой вид
    if (n < 0) {
        perror("need n > 0\n");
    }

    const char *file_name = argv[2];


    printf("введенная команда: %d,  %s \n", n, file_name);

    int mode = O_RDONLY;//O_RDONLY - чтению,  O_WRONLY - записи
    file_input = open(file_name, mode);
    if (file_input == -1)
        perror("file opening error!\n");

    stat(file_name, &file_stat); //вносит в структуру информацию, содержащуюся в файле, связанном с указателем filename.

    long size = file_stat.st_size;

    //буфер для хранения текста
    char stack[size + 1];
    stack[size] = '\0';
    int lines = 0, head = -1;

    for (int offset = 1; offset <= size; ++offset) {
        if (lseek(file_input, -offset, SEEK_END) != -1L) {//SEEK_END - флаг на то, что мы смотрим с конца
            char tmp[1] = "\0";
            read(file_input, tmp, 1);
            if (tmp[0] == '\n') {
                if (offset == 1) { //блок на пустую строку
                    continue;
                } else {
                    ++lines;
                }
            }
            if (lines == n) {
                break;
            }
            stack[++head] = tmp[0];
        }
    }


    while (head >= 0) {
        printf("%c", stack[head--]);
    }

    return 0;
}
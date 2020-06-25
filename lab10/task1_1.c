#include <stdio.h>
#include <zconf.h>

int main() {
    if (unlink("test.txt") == -1) { //удаляем ссылку и проверяем на ошибку
        perror("error!\n");
        return -1;
    }
    return 0;
}
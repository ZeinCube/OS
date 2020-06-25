#include <stdio.h>


int main() {
    char c;
    FILE *f = fopen("test.txt", "r");
    if (!f) {
        perror("file opening error!\n");
        return 1;
    }
    int i = 0;

    while (1) {
        fseek(f, 0, SEEK_SET);//смещаем указатель на начало файла

        while ((c = fgetc(f)) != EOF) {
            printf("%d\n", i);
            i++;
        }
    }
}
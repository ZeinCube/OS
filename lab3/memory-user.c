#include <stdlib.h>

_Noreturn static void memory_user(long bytes) {
    int *array = (int *)malloc(bytes); //выделяем динамически память под массив int
    while (1) {
        for (int i = 0; i < bytes / sizeof(int); ++i) { //бесконечный цикл по элементам
            array[i] = random() % 1000;
        }
    }
}
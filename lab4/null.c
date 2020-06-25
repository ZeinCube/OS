#include <stdio.h>

int global;
int main()
//static int null()
{
    int *a = NULL; // создаем нулевой указатель
    printf("%d", *a); // пытаемся обратиться к нему и напечатать значение
    return 0;
}
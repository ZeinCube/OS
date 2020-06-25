
#include <stdio.h>
#include <stdlib.h>

int global;//глобальная целочисленная переменная

static int aspace ()
{
    int local = 5;//локальная целочисленная переменная №1
    void *p = malloc(128); //malloc №1 (динамическое выделение памяти(128 байт))
    void *p2 = malloc(256); //malloc №2 (динамическое выделение памяти(256 байт))
    int local2 = 25; //локальная целочисленная переменная №2

    printf ("Address of main is %p\n", aspace); // печать адреса первой инструкции машинного языка
    printf ("Address of global is %p\n", &global); // печать адреса глобальной переменной
    printf ("Address of p is %p\n", p); // печать адреса, который вернул malloc
    printf ("Address of p2 is %p\n", p2); // печать адреса, который вернул второй malloc
    printf ("Address of local is %p\n", &local); //печать адреса локальной переменной
    printf ("Address of local2 is %p\n", &local2); // печать адреса второй локальной переменной
    printf ("Address of &p is %p\n", &p);

    return 0;
}
